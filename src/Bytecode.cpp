#include "/home/professor/mystuffs/MyCompiler/include/Bytecode.h"
#include <sstream>

static std::string opName(OpCode op){
    switch(op){
        case OpCode::PUSH_CONST: return "PUSH_CONST";
        case OpCode::LOAD_VAR:   return "LOAD_VAR";
        case OpCode::STORE_VAR:  return "STORE_VAR";
        case OpCode::ADD:        return "ADD";
        case OpCode::SUB:        return "SUB";
        case OpCode::MUL:        return "MUL";
        case OpCode::DIV:        return "DIV";
        case OpCode::PRINT:      return "PRINT";
        case OpCode::HALT:       return "HALT";
    }
    return "UNKNOWN";
}

std::string disassemble(const Chunk& chunk){
    std::ostringstream out;

    for(size_t i=0;i<chunk.size();i++){
        const Instruction& instr = chunk[i];
        out<<i<<": "<<opName(instr.op);

        if(instr.op == OpCode::PUSH_CONST)out<<" "<<instr.operand;
        else if(instr.op == OpCode::LOAD_VAR || instr.op == OpCode::STORE_VAR)out<<" "<<instr.varName;
        out<<"\n";
    }
    return out.str();
}
