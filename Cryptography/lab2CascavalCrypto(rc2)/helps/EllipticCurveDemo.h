#pragma once

#include <vector>

struct Point {
    std::vector<unsigned char> x;
    std::vector<unsigned char> y;
    bool infinity = false;
};

void print_point(const char* name, const Point& point);
Point generator_point();
std::vector<unsigned char> generate_private_key();
Point scalar_mult(const std::vector<unsigned char>& scalar, const Point& point);
std::vector<unsigned char> derive_shared_secret(const std::vector<unsigned char>& private_key,
                                               const Point& peer_public_key);
std::vector<unsigned char> derive_rc2_key(const std::vector<unsigned char>& shared_secret);
