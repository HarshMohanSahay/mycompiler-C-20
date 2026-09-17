#include "/home/professor/mystuffs/MyCompiler/include/Compiler.h"
#include <stdexcept>

void Compiler::emit(Instruction instr){
    chunk_.push_back(std::move(instr));
}

Chunk Compiler::compile(const std::vector<std::unique_ptr<Stmt>>& program){
    chunk_.clear();

    for(const auto& stmt:program){
        compileStmt(stmt.get());
    }

    emit(Instruction{OpCode::HALT});
    return chunk_;
}

void Compiler::compileStmt(const Stmt* stmt){
    switch(stmt->type){
        case StmtType::ASSIGN:{
            const auto* s = static_cast<const AssignStmt*>(stmt);
            compileExpr(s->value.get());
            emit(Instruction{OpCode::STORE_VAR,0.0,s->name});
            break;
        }

        case StmtType::PRINT:{
            const auto* s = static_cast<const PrintStmt*>(stmt);
            compileExpr(s->value.get());
            emit(Instruction{OpCode::PRINT});
            break;
        }
    }
}

void Compiler::compileExpr(const Expr* expr){
    switch(expr->type){
        case ExprType::NUMBER:{
            const auto* e = static_cast<const NumberExpr*>(expr);
            emit(Instruction{OpCode::PUSH_CONST,e->value});
            break;
        }
        case ExprType::VARIABLE:{
            const auto* e = static_cast<const VariableExpr*>(expr);
            emit(Instruction{OpCode::LOAD_VAR,0.0,e->name});
            break;
        }
        case ExprType::BINARY:{
            const auto* e = static_cast<const BinaryExpr*>(expr);
            compileExpr(e->left.get());
            compileExpr(e->right.get());
            switch(e->op){
                case '+':emit(Instruction{OpCode::ADD});break;
                case '-':emit(Instruction{OpCode::SUB});break;
                case '*':emit(Instruction{OpCode::MUL});break;
                case '/':emit(Instruction{OpCode::DIV});break;
                default:
                  throw std::runtime_error(std::string("Compiler error:unknown operator'")+e->op+"'");
            }
            break;
        }
    }
}