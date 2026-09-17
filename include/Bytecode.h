#pragma once
#include <string>
#include <vector>

// This file defines the bytecode instructions for our virtual machine.
// Bytecode is a low-level representation of the program that the VM can execute efficiently.

// Enumeration of all possible bytecode operations (opcodes).
enum class OpCode{
    PUSH_CONST,   // Push a constant value onto the stack
    LOAD_VAR,     // Push the value of a variable onto the stack
    STORE_VAR,    // Pop a value from the stack and store it in a variable
    ADD,          // Pop two values, add them, push the result
    SUB,          // Pop two values, subtract them (second - first), push the result
    MUL,          // Pop two values, multiply them, push the result
    DIV,          // Pop two values, divide them (second / first), push the result
    PRINT,        // Pop a value and print it to the console
    HALT          // Stop the virtual machine
};

// Represents a single bytecode instruction.
struct Instruction{
    OpCode op;        // The operation to perform.
    double operand = 0.0; // Used for PUSH_CONST: the constant value to push.
    std::string varName; // Used for LOAD_VAR and STORE_VAR: the variable name.
};

// A chunk is a sequence of bytecode instructions (i.e., a compiled function or program).
using Chunk = std::vector<Instruction>;

// Converts a chunk of bytecode into a human-readable string (used for debugging).
std::string disassemble(const Chunk& chunk);