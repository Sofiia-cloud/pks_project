// Token.h
#ifndef TOKEN_H
#define TOKEN_H

#include <string>  // ← ЭТО КЛЮЧЕВОЕ: добавляем include для std::string

enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    COMMENT,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;  // теперь std::string определён
};

#endif