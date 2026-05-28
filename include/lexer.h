#pragma once
#include <cstddef>
#include <string>
#include <vector>

enum class Token {
    LEFTBRACE,
    RIGHTBRACE,
    STRING,
    STRING_OPENER,
    COLON,
    COMMA,
    INTEGER,
    TRUE,
    FALSE,
    NILL,
    LEFTBRACKET,
    RIGHTBRACKET,
    INVALID
};

class Tokenizer {
public:
    Tokenizer(const std::string& str);
    void stringParse();

    const std::string& source;
    std::string::const_iterator it;
    std::vector<Token> tokens;
    static bool isAllDigits(const std::string& str);
};
