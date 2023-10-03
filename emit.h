#ifndef __EMIT_H__
#define __EMIT_H__

#include <iostream>
#include <string>
#include <fstream>

namespace tc {

class Emit
{
    public:
    Emit()
    {
        code = "";
    }

    void emit(std::string c)
    {
        code += c;
    }

    void emitLine(std::string c)
    {
        code += c + "\n";
    }

    void write(std::string output)
    {
        std::ofstream out(output);
        out << code;
        out.close();
        std::cout << "wrote\n";
    }
    
    private:
    std::string code;
};

}

#endif