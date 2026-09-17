#pragma once
#include <string>

// This file defines the tokens that our lexer can recognize.
// Think of tokens as the "words" and "punctuation" of our programming language.

// Enumeration of all possible token types.
enum class TokenType {
    NUMBER,        // Represents numeric literals like 42 or 3.14
    IDENTIFIER,    // Represents variable names like x, total, or myVar
    PLUS,          // The + operator
    MINUS,         // The - operator
    STAR,          // The * operator (for multiplication)
    SLASH,         // The / operator (for division)
    EQUAL,         // The = operator (for assignment)
    SEMICOLON,     // The ; character (ends statements)
    LPAREN,        // The ( character (left parenthesis)
    RPAREN,        // The ) character (right parenthesis)
    PRINT,         // The keyword "print" (for output)
    END_OF_FILE,   // Special token that marks the end of input
    UNKNOWN        // Used for characters we don't recognize (helps with error messages)
};

// Represents a single token (a "word" or "symbol" from the source code).
struct Token{
    TokenType type;        // What kind of token this is (e.g., NUMBER, PLUS)
    std::string lexeme;    // The actual text of the token (e.g., "42", "+", "x")
    double numberValue;    // For NUMBER tokens, this stores the numeric value
    int line;              // Which line number this token appeared on (for error messages)
};

// Debug helper: converts a TokenType enum to a readable string.
// This helps us print tokens in a nice format when debugging.
inline std::string tokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::NUMBER:      return "NUMBER";
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        case TokenType::PLUS:        return "PLUS";
        case TokenType::MINUS:       return "MINUS";
        case TokenType::STAR:        return "STAR";
        case TokenType::SLASH:       return "SLASH";
        case TokenType::EQUAL:       return "EQUAL";
        case TokenType::SEMICOLON:   return "SEMICOLON";
        case TokenType::LPAREN:      return "LPAREN";
        case TokenType::RPAREN:      return "RPAREN";
        case TokenType::PRINT:       return "PRINT";
        case TokenType::END_OF_FILE: return "EOF";
        default:                     return "UNKNOWN";
    }
}

// example 
// x = 42 + y;
// [ IDENTIFIER | "x"  | 0    | 1 ]
// [ EQUAL      | "="  | 0    | 1 ]
// [ NUMBER     | "42" | 42.0 | 1 ]
// [ PLUS       | "+"  | 0    | 1 ]
// [ IDENTIFIER | "y"  | 0    | 1 ]
// [ SEMICOLON  | ";"  | 0    | 1 ]
// [ END_OF_FILE| ""   | 0    | 1 ]