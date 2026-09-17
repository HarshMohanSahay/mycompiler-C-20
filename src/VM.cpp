#include "./VM.h"
#include<iostream>
#include <stdexcept>

void VM::push(double value){
    stack_.push_back(value);
}

double VM::pop(){
    if(stack_.empty()){
        throw std::runtime_error("VM error:stack underflow(popped an empty stack)");
    }

    double value = stack_.back();
    stack_.pop_back();
    return value;
}


void VM::run(const Chunk& chunk){
    size_t ip = 0;

    while(ip < chunk.size()){
        const Instruction& instr = chunk[ip];

        switch(instr.op){
            case OpCode::PUSH_CONST:
                 push(instr.operand);
                 break;

            case OpCode::LOAD_VAR:{
                auto it = variables_.find(instr.varName);
                if(it == variables_.end()){
                    throw std::runtime_error("VM error:undefined variable '"+instr.varName+"'");
                }
                push(it->second);
                break;
            }     

            case OpCode::STORE_VAR:{
                double value = pop();
                variables_[instr.varName] = value;
                break;
            }

            case OpCode::ADD:{
                double b = pop();
                double a = pop();
                push(a+b);
                break;
            }

            case OpCode::SUB:{
                double b = pop();
                double a = pop();
                push(a+b);
                break;
            }

            case OpCode::MUL:{
                double b = pop();
                double a = pop();
                push(a*b);
                break;
            }

            case OpCode::DIV:{
                double b = pop();
                double a = pop();
                if(b == 0.0)throw std::runtime_error("VM error:division by zero ");
                push(a/b);
                break;
            }

            case OpCode::PRINT:{
                double value = pop();
                std::cout<<value<<std::endl;
                break;
            }

            case OpCode::HALT:
                 return;

            default:
                throw std::runtime_error("VM error:unknown opcode");     
        }
        ip++;
    }
}