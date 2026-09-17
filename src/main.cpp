#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "VM.h"
#include "Bytecode.h"

static std::string readFile(const std::string& path){
    std::ifstream file(path);
    if(!file){
        throw std::runtime_error("Could not open file:"+path);
    }
    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}


int main(int argc,char** argv){
    if(argc<2){
        std::cerr<<"Usage: "<<argv[0]<<" <source-file.mini> [--debug]\n";
        return 1;
    }

    bool debug = (argc >= 3 && std::string(argv[2]) == "--debug");
    if(!debug && argc >= 3){
        std::cerr<<"Usage: "<<argv[0]<<" <source-file.mini> [--debug]\n";
        return 1;
    }

    try{
        std::string source = readFile(argv[1]);

        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        std::vector<std::unique_ptr<Stmt>> program = parser.parseProgram();

        Compiler compiler;
        Chunk bytecode = compiler.compile(program);

        if(debug){
            std::cout << "-----TOKENS-----\n";
            for(const auto& token : tokens){
                std::cout << token.line << ": "
                          << tokenTypeName(token.type) << " '"
                          << token.lexeme << "'\n";
            }
            std::cout << "\n-----BYTECODE----\n";
            std::cout << disassemble(bytecode);
            std::cout << "\n-----OUTPUT----\n";
        }


        VM vm;
        vm.run(bytecode);
    }catch(const std::exception& ex){
        std::cerr<<"Error: "<<ex.what() << std::endl;
        return 1;
    }

    return 0;
}
