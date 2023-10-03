#ifndef __LEXER_H__
#define __LEXER_H__
#include <iostream>
#include <string>
#include "token.h"
#include <memory>
#include <unordered_set>
#include <assert.h>

namespace tc 
{
class Lexer
{
    public:
    Lexer(std::string src);
    void nextChar(void);
    char peek(void);
    void abort(std::string message)
    {
        std::cout << "Error: " + message + "\n";
        assert(0==1);
    }
    void skipWhitespace(void);
    void skipComment(void);
    Token getToken(void);
    char getCurChar(void);
    bool isEOF(const Token &token);

    private:
    std::string source;
    char curChar;
    int curPos;   
    int sourceLen;
    bool checkIsKeyword(const Token &token);
};
}
#endif