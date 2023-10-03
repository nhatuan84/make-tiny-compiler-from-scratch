#include "token.h"
#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

int main() 
{
    std::ifstream inFile;
    inFile.open("../code.tc");

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string source = strStream.str();
    
    #if 0
	tc::Lexer lexer(source);
    tc::Token token = lexer.getToken();
	while (!lexer.isEOF(token))
    {
		std::cout << token.value << "\n";
        token = lexer.getToken();
    }
    #else
    tc::Parser parser (source);
    parser.program();
    std::cout << "Parsing completed\n";
    parser.end("code.py");
    #endif
    
    return 0;
}
