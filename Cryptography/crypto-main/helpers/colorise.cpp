// Твой основной код на C++ (оставляем как есть, только убираем дублирование)

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../include/utils.hpp"
#include <cstdarg>

// Теги цветов больше не используются: вывод остаётся без ANSI-кодов
inline const std::unordered_map<std::string, std::string>& getColors() {
    static const std::unordered_map<std::string, std::string> COLORS = {
        {"<red>", ""},
        {"<green>", ""},
        {"<yellow>", ""},
        {"<blue>", ""},
        {"<magenta>", ""},
        {"<cyan>", ""},
        {"<white>", ""},
        {"<reset>", ""},
        {"<enc>", "Encrypt: "},
        {"<dec>", "Decrypt: "},
        {"<key>", "Key: "}
    };
    return COLORS;
}

void color(const std::string& colorCode) {
    (void)colorCode;
}

void resetColor() {
    std::cout << std::endl;
}

std::string echo(const std::string& message) {
    std::string result = "";
    const auto& COLORS = getColors();
    std::vector<std::string> tokens = split(message.c_str());

    for (size_t i = 0; i < tokens.size(); i++) {
        auto it = COLORS.find(tokens[i]);
        if (it != COLORS.end()) {
            result += it->second;
        } else {
            result += tokens[i];
        }
        if (i + 1 < tokens.size()) {
            result += " ";
        }
    }
    return result;
}

// МОСТ ДЛЯ C-КОДА (C-Compatible Wrapper)

extern "C" {
    // Безопасный аналог printf с поддержкой ваших тегов
    void c_print_format(const char* format, ...) {
        if (!format) return;

        va_list args;
        va_start(args, format);
        va_list args_copy;
        va_copy(args_copy, args);
        int len = std::vsnprintf(nullptr, 0, format, args_copy);
        va_end(args_copy);

        std::string formatted_msg(len, '\0');
        std::vsnprintf(&formatted_msg[0], len + 1, format, args);
        va_end(args);

        // Передаем готовый текст в ваш существующий метод echo
        std::string final_output = echo(formatted_msg);
        std::cout << final_output << std::endl;
    }
}
