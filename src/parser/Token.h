#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    COMMENT,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

#endif