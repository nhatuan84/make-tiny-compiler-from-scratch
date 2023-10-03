#include "parser.h"

namespace tc
{
    Parser::Parser(std::string &source)
    {
        indent_count = 0;
        lexer = std::make_shared<Lexer>(source);
        emit = std::make_shared<Emit>();
        nextToken();
        nextToken();
    }

    bool Parser::checkToken(TokenType t)
    {
        return (curToken.type == t);
    }
    bool Parser::checkPeek(TokenType t)
    {
        return (peekToken.type == t);
    }
    bool Parser::match(TokenType t)
    {
        if(!checkToken(t))
        {
            std::cout << "expect " << t << " != " << curToken.type << "\n";
            abort("it must match token");
        }
        return true;
    }
    void Parser::nextToken()
    {
        curToken = peekToken;
        peekToken = lexer->getToken();
    }

    /*
    {} means zero or more, 
    [] means zero or one, 
    + means one or more of whatever is to the left, 
    () is just for grouping, and | is a logical or

    program ::= {statement}
    statement ::= "PRINT" (expression | string) nl
        | "IF" comparison nl {statement} nl "ELSE" nl {statement} nl "ENDIF" nl
        | "WHILE" comparison nl {statement} "ENDWHILE" nl
        | "PASS" nl
        | "LET" ident "=" expression nl
        | "INPUT" ident nl
    comparison ::= expression (("==" | "!=" | ">" | ">=" | "<" | "<=") expression)+
    expression ::= term {( "-" | "+" ) term}
    term ::= unary {( "/" | "*" ) unary}
    unary ::= ["+" | "-"] primary
    primary ::= number | ident
    nl ::= '\n'+
    */
    void Parser::program(void)
    {
        std::cout << "program\n";
        while (!checkToken(_EOF))
        {
            statement();
        }
    }

    void Parser::statement(void)
    {
        std::cout << "statement\n";
        if (checkToken(PRINT))
        {
            std::cout << "PRINT\n";
            nextToken();
            if (checkToken(STRING) || checkToken(NUMBER) || checkToken(ID))
            {
                for(int i=0; i<indent_count; i++)
                {
                    emit->emit("\t");
                }
                if(curToken.type == STRING)
                {
                    emit->emit("print (\"" + curToken.value + "\")\n");
                }
                else if(curToken.type == NUMBER || curToken.type == ID)
                {
                    emit->emit("print (" + curToken.value + ")\n");
                }
                
            }
            else
            {
                statement();
            }
            nextToken();
            nl();
            std::cout << "exit PRINT\n";
        }
        else if (checkToken(IF))
        {
            for(int i=0; i<indent_count; i++)
            {
                emit->emit("\t");
            }
            std::cout << "IF\n";
            emit->emit("if ");
            indent_count ++;
            nextToken();
            comparison();
            emit->emit(":\n");
            nextToken();
            nl();
            while(!checkToken(ELSE) && !checkToken(ENDIF))
            {
                statement();
            }
            if (checkToken(ELSE))
            {
                for(int i=0; i<indent_count-1; i++)
                {
                    emit->emit("\t");
                }
                std::cout << "ELSE\n";
                emit->emit("else:\n");
                nextToken();
                nl();
                while(!checkToken(ENDIF))
                {
                    statement();
                }
            }
            match(ENDIF);
            indent_count --;
            nextToken();
            nl();
            std::cout << "exit IF\n";
        }
        else if (checkToken(WHILE))
        {
            for(int i=0; i<indent_count; i++)
            {
                emit->emit("\t");
            }
            nextToken();
            emit->emit("while ");
            indent_count ++;
            comparison();
            emit->emit(":\n");
            nextToken();
            nl();
            while(!checkToken(ENDWHILE))
            {
                statement();
            }
            match(ENDWHILE);
            indent_count --;
            nextToken();
            nl();
        }
        else if (checkToken(LET))
        {
            for(int i=0; i<indent_count; i++)
            {
                emit->emit("\t");
            }
            std::cout << "LET\n";
            nextToken();
            match(ID);
            emit->emit(curToken.value);
            nextToken();
            match(EQ);
            emit->emit(" = ");
            nextToken();
            expression();
            emit->emit("\n");
            nextToken();
            nl();
        }
        else if (checkToken(INPUT))
        {
            for(int i=0; i<indent_count; i++)
            {
                emit->emit("\t");
            }
            std::cout << "INPUT\n";
            nextToken();
            match(ID);
            emit->emit(curToken.value + " = int(input())\n");
            nextToken();
            nl();
        }
        else if (checkToken(PASS))
        {
            for(int i=0; i<indent_count; i++)
            {
                emit->emit("\t");
            }
            std::cout << "PASS\n";
            emit->emit("pass\n");
            nextToken();
            nl();
        }
    }
    bool Parser::isCompareOps(void)
    {
        if(peekToken.type > START_COMPARE_OPS && peekToken.type < END_COMPARE_OPS)
        {
            return true;
        }
        return false;
    }
    void Parser::comparison(void)
    {
        std::cout << "comparison\n";
        expression();
        if(isCompareOps())
        {
            nextToken();
            emit->emit(" " + curToken.value + " ");
            nextToken();
            expression();
        }
        while(isCompareOps())
        {
            nextToken();
            emit->emit(" " + curToken.value + " ");
            nextToken();
            expression();
            emit->emit(curToken.value);
        }
    }
    void Parser::expression(void)
    {
        std::cout << "expression\n";
        term();
        while(checkPeek(MINUS) || checkPeek(PLUS))
        {
            nextToken();
            emit->emit(" " + curToken.value + " ");
            nextToken();
            term();
        }
    }
    void Parser::term(void)
    {
        std::cout << "term\n";
        unary();
        while(checkPeek(ASTERISK) || checkPeek(SLASH))
        {
            nextToken();
            emit->emit(" " + curToken.value + " ");
            nextToken();
            unary();
        }
    }
    void Parser::unary(void)
    {
        std::cout << "unary\n";
        //pos/neg number
        if(checkToken(PLUS) || checkToken(MINUS))
        {
            emit->emit(curToken.value);
            nextToken();
        }
        primary();
    }
    void Parser::primary(void)
    {
        std::cout << "primary ";
        if(checkToken(NUMBER) || checkToken(ID))
        {
            std::cout << curToken.value << "\n";
            emit->emit(curToken.value);
        }
    }
    void Parser::nl(void)
    {
        match(NEWLINE);
        while (checkToken(NEWLINE))
        {
            nextToken();
        }
    }
}