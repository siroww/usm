#include "../helps/EllipticCurveDemo.h"

#include <array>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/obj_mac.h>
#include <openssl/rand.h>

namespace {
constexpr int coordinate_size = 32;

using GroupPtr = std::unique_ptr<EC_GROUP, decltype(&EC_GROUP_free)>;
using PointPtr = std::unique_ptr<EC_POINT, decltype(&EC_POINT_free)>;
using BnPtr = std::unique_ptr<BIGNUM, decltype(&BN_free)>;
using BnCtxPtr = std::unique_ptr<BN_CTX, decltype(&BN_CTX_free)>;

GroupPtr create_group() {
    GroupPtr group(EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1), EC_GROUP_free);
    if (!group) {
        throw std::runtime_error("Не удалось создать группу P-256");
    }
    return group;
}

BnCtxPtr create_context() {
    BnCtxPtr context(BN_CTX_new(), BN_CTX_free);
    if (!context) {
        throw std::runtime_error("Не удалось выделить контекст OpenSSL");
    }
    return context;
}

Point point_to_coordinates(const EC_GROUP* group, const EC_POINT* point, BN_CTX* context) {
    BnPtr x(BN_new(), BN_free);
    BnPtr y(BN_new(), BN_free);
    if (!x || !y ||
        EC_POINT_get_affine_coordinates(group, point, x.get(), y.get(), context) != 1) {
        throw std::runtime_error("Не удалось получить координаты точки");
    }

    Point result;
    result.x.resize(coordinate_size);
    result.y.resize(coordinate_size);
    if (BN_bn2binpad(x.get(), result.x.data(), coordinate_size) != coordinate_size ||
        BN_bn2binpad(y.get(), result.y.data(), coordinate_size) != coordinate_size) {
        throw std::runtime_error("Не удалось сериализовать координаты точки");
    }
    return result;
}

PointPtr point_from_coordinates(const EC_GROUP* group, const Point& coordinates,
                                BN_CTX* context) {
    if (coordinates.infinity || coordinates.x.size() != coordinate_size ||
        coordinates.y.size() != coordinate_size) {
        throw std::invalid_argument("Некорректные координаты точки P-256");
    }

    BnPtr x(BN_bin2bn(coordinates.x.data(), coordinate_size, nullptr), BN_free);
    BnPtr y(BN_bin2bn(coordinates.y.data(), coordinate_size, nullptr), BN_free);
    PointPtr point(EC_POINT_new(group), EC_POINT_free);
    if (!x || !y || !point ||
        EC_POINT_set_affine_coordinates(group, point.get(), x.get(), y.get(), context) != 1 ||
        EC_POINT_is_on_curve(group, point.get(), context) != 1) {
        throw std::invalid_argument("Точка не принадлежит кривой P-256");
    }
    return point;
}

BnPtr scalar_from_bytes(const std::vector<unsigned char>& scalar, const EC_GROUP* group) {
    if (scalar.empty() || scalar.size() > coordinate_size) {
        throw std::invalid_argument("Секретный скаляр должен содержать от 1 до 32 байт");
    }

    BnPtr value(BN_bin2bn(scalar.data(), static_cast<int>(scalar.size()), nullptr), BN_free);
    BnPtr order(BN_new(), BN_free);
    if (!value || !order || EC_GROUP_get_order(group, order.get(), nullptr) != 1 ||
        BN_is_zero(value.get()) || BN_cmp(value.get(), order.get()) >= 0) {
        throw std::invalid_argument("Секретный скаляр должен быть в диапазоне [1, n-1]");
    }
    return value;
}
}  // namespace

void print_point(const char* name, const Point& point) {
    const std::ios::fmtflags original_flags = std::cout.flags();
    const char original_fill = std::cout.fill();

    std::cout << name << " (x): ";
    for (unsigned char byte : point.x) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(byte);
    }

    std::cout << " (y): ";
    for (unsigned char byte : point.y) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(byte);
    }
    std::cout.flags(original_flags);
    std::cout.fill(original_fill);
    std::cout << '\n';
}

Point generator_point() {
    GroupPtr group = create_group();
    BnCtxPtr context = create_context();
    return point_to_coordinates(group.get(), EC_GROUP_get0_generator(group.get()), context.get());
}

std::vector<unsigned char> generate_private_key() {
    GroupPtr group = create_group();
    BnPtr order(BN_new(), BN_free);
    BnPtr range(BN_new(), BN_free);
    BnPtr value(BN_new(), BN_free);
    if (!order || !range || !value ||
        EC_GROUP_get_order(group.get(), order.get(), nullptr) != 1 ||
        BN_copy(range.get(), order.get()) == nullptr || BN_sub_word(range.get(), 1) != 1 ||
        BN_priv_rand_range(value.get(), range.get()) != 1 || BN_add_word(value.get(), 1) != 1) {
        throw std::runtime_error("Не удалось сгенерировать секретный ключ P-256");
    }

    std::vector<unsigned char> result(coordinate_size);
    if (BN_bn2binpad(value.get(), result.data(), coordinate_size) != coordinate_size) {
        throw std::runtime_error("Не удалось сериализовать секретный ключ P-256");
    }
    return result;
}

Point scalar_mult(const std::vector<unsigned char>& scalar, const Point& point) {
    GroupPtr group = create_group();
    BnCtxPtr context = create_context();
    BnPtr value = scalar_from_bytes(scalar, group.get());
    PointPtr input = point_from_coordinates(group.get(), point, context.get());
    PointPtr result(EC_POINT_new(group.get()), EC_POINT_free);
    if (!result ||
        EC_POINT_mul(group.get(), result.get(), nullptr, input.get(), value.get(),
                     context.get()) != 1 ||
        EC_POINT_is_at_infinity(group.get(), result.get()) == 1) {
        throw std::runtime_error("Не удалось вычислить скалярное произведение точки");
    }
    return point_to_coordinates(group.get(), result.get(), context.get());
}

std::vector<unsigned char> derive_shared_secret(const std::vector<unsigned char>& private_key,
                                                const Point& peer_public_key) {
    return scalar_mult(private_key, peer_public_key).x;
}

std::vector<unsigned char> derive_rc2_key(const std::vector<unsigned char>& shared_secret) {
    std::array<unsigned char, EVP_MAX_MD_SIZE> digest{};
    unsigned int digest_size = 0;
    if (shared_secret.empty() ||
        EVP_Digest(shared_secret.data(), shared_secret.size(), digest.data(), &digest_size,
                   EVP_sha256(), nullptr) != 1 ||
        digest_size < 16) {
        throw std::runtime_error("Не удалось получить ключ RC2 из общего секрета");
    }
    return std::vector<unsigned char>(digest.begin(), digest.begin() + 16);
}
