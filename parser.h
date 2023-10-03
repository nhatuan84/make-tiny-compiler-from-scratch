#ifndef __PARSER_H__
#define __PARSER_H__
#include "token.h"
#include "lexer.h"
#include "emit.h"
#include <memory>
#include <assert.h>

namespace tc
{
class Parser
{
    public:
    Parser(std::string &source);
    bool checkToken(TokenType t);
    bool checkPeek(TokenType t);
    bool match(TokenType t);
    void nextToken(void);
    void abort(std::string message)
    {
        std::cout << "Error: " + message + "\n";
        assert(0==1);
    }
    void program(void);
    void end(std::string output)
    {
        emit->write(output);
    }
    private:
    Token curToken;
    Token peekToken;
    int indent_count;
    std::shared_ptr<Lexer> lexer;
    std::shared_ptr<Emit> emit;
    bool isCompareOps(void);
    void statement(void);
    void expression(void);
    void nl(void);
    void comparison(void);
    void term(void);
    void unary(void);
    void primary(void);
    void debug(void)
    {
        std::cout << curToken.type << " " << peekToken.type << "\n";
    }
};
}

#endif