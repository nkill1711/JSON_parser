#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "lexer.h"
#include <exception>
#include <string>
#include <utility>

// Base exception class
class JsonException : public std::exception {
protected:
    std::string message;
    
public:
    explicit JsonException(std::string  msg) : message(std::move(msg)) {}
    
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidJsonException : public JsonException {
public:
    explicit InvalidJsonException(Token token) 
        : JsonException("Invalid json: ") {}
};

#endif 