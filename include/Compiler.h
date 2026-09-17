#pragma once
#include <memory>
#include "AST.h"
#include "Bytecode.h"

// The Compiler class takes an AST (vector of statements) and translates it
// into a sequence of bytecode instructions that our virtual machine can execute.
// Think of it as a translator from high-level code to low-level machine code.
class Compiler{
   public:
     // Main entry point: compiles the whole program (a list of statements)
     // into a chunk of bytecode.
     Chunk compile(const std::vector<std::unique_ptr<Stmt>>& program);

   private:
      // Holds the bytecode instructions as we generate them.
      Chunk chunk_;

      // Compiles a single statement (assignment or print).
      void compileStmt(const Stmt* stmt);

      // Compiles a single expression (number, variable, or binary operation).
      void compileExpr(const Expr* expr);

      // Adds an instruction to the end of the chunk.
      void emit(Instruction instr);
};