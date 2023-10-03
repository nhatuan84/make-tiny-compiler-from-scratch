#ifndef __TOKEN_H__
#define __TOKEN_H__
#include <iostream>
#include <string>
#include <unordered_map>

namespace tc 
{
    typedef enum
    {
        UNKNOWN,
        START_GENERALS,
        _EOF,
        NEWLINE,
        NUMBER,
        ID,
        STRING,
        END_GENERALS,
        START_KEYWORDS,
        PRINT,
        INPUT,
        LET,
        IF,
        PASS,
        ELSE,
        THEN,
        ENDIF,
        WHILE,
        ENDWHILE,
        END_KEYWORDS,
        START_OPERATORS,
        EQ,
        PLUS,
        MINUS,
        ASTERISK,
        SLASH,
        END_OPERATORS,
        START_COMPARE_OPS,
        EQEQ,
        NOTEQ,
        LT,
        LTEQ,
        GT,
        GTEQ,
        END_COMPARE_OPS,
        NUM_TOKENTYPES
    } TokenType;
    const std::unordered_map<std::string, TokenType> keywords = {{"PRINT", PRINT},
                                                                {"INPUT",INPUT},
                                                                {"LET", LET},
                                                                {"IF", IF},
                                                                {"PASS", PASS},
                                                                {"ELSE", ELSE},
                                                                {"THEN", THEN},
                                                                {"ENDIF", ENDIF},
                                                                {"WHILE", WHILE},
                                                                {"ENDWHILE", ENDWHILE}};
    std::string convertString(TokenType t);
    TokenType isKeyword(const std::string &text);

    class Token
    {
        public:
        Token();
        Token(TokenType t, std::string v="");
        void operator=(const Token& rhs);
        std::string value;
        TokenType type;
    };
}

#endif