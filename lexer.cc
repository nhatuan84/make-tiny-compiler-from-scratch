#include "lexer.h"

namespace tc 
{
    Lexer::Lexer(std::string src)
    {
        source = src + "\n";
        curChar = 0;
        curPos = -1; 
        sourceLen = source.length();
    }
    void Lexer::nextChar(void)
    {
        curPos += 1;
        if (curPos >= sourceLen)
        {
            curChar = '\0';
        }
        else
        {
            curChar = source.at(curPos);
        }
    }
    char Lexer::peek(void)
    {
        if (curPos + 1 >= sourceLen)
        {
            return '\0';
        }
        return source.at(curPos + 1);
    }
    bool Lexer::isEOF(const Token &token)
    {
        return (token.type == _EOF);
    }
    void Lexer::skipWhitespace(void)
    {
        while (curChar == ' ' || curChar == '\t' || curChar == '\r')
        {
            nextChar();
        }
    }
    void Lexer::skipComment(void)
    {
        if(curChar == '#')
        {
            while (curChar != '\n')
            {
                nextChar();
            }
        }
    }
    Token Lexer::getToken(void)
    {
        nextChar();
        skipComment();
        skipWhitespace();

        if (curChar == '+')
        {
            return Token(PLUS);
        }
        else if (curChar == '-')
        {
            return Token(MINUS);
        }
        else if (curChar == '*')
        {
            return Token(ASTERISK);
        }
        else if (curChar == '/')
        {
            return Token(SLASH);
        }
        else if (curChar == '\n')
        {
            return Token(NEWLINE);
        }
        else if (curChar == '\0')
        {
            return Token(_EOF);
        }
        else if (curChar == '=')
        {
            if(peek() == '=')
            {
                nextChar();
                return Token(EQEQ);
            }
            else
            {
                return Token(EQ);
            }
        }
        else if (curChar == '!')
        {
            if(peek() == '=')
            {
                nextChar();
                return Token(NOTEQ);
            }
            else
            {
                abort("not supported\n");
            }
        }
        else if (curChar == '<')
        {
            if(peek() == '=')
            {
                nextChar();
                return Token(LTEQ);
            }
            else
            {
                return Token(LT);
            }
        }
        else if (curChar == '>')
        {
            if(peek() == '=')
            {
                nextChar();
                return Token(GTEQ);
            }
            else
            {
                return Token(GT);
            }
        }
        else if (curChar == '\"')
        {
            nextChar();
            int startPos = curPos;
            while (curChar != '\"')
            {
                nextChar();
            }
            std::string text = source.substr(startPos, curPos - startPos);
            return Token(STRING, text);
        }
        else if (isalpha(curChar))
        {
            int startPos = curPos;
            while (isalpha(peek()) || isdigit(peek()))
            {
                nextChar();
            }
            std::string text = source.substr(startPos, curPos - startPos + 1);
            TokenType t = tc::isKeyword(text);
            if(t != UNKNOWN)
            {
                return Token(t, text);
            }
            else
            {
                return Token(ID, text);
            }
        }
        else if (isdigit(curChar))
        {
            int startPos = curPos;
            while (isdigit(peek()))
            {
                nextChar();
            }
            if(peek() == '.')
            {
                nextChar();
                if(!isdigit(peek()))
                {
                    abort("it must be number\n");
                }
                else
                {
                    nextChar();
                }
                while (isdigit(peek()))
                {
                    nextChar();
                }
            }
            std::string text = source.substr(startPos, curPos - startPos + 1);
            
            return Token(NUMBER, text);
        }
        return Token(UNKNOWN);
    }
    char Lexer::getCurChar(void)
    {
        return curChar;
    }
}