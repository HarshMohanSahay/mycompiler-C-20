#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "AST.h"

// The Parser takes the tokens from the Lexer and builds an Abstract Syntax Tree (AST)
// based on the grammar of our language.
// Think of it like understanding the grammar of a sentence to figure out its structure.

// Grammar rules for our Mini-like language:
//   program     -> statement* EOF          (zero or more statements followed by end-of-file)
//   statement   -> assignStmt | printStmt  (either an assignment or a print statement)
//   assignStmt  -> IDENTIFIER "=" expression ";"  (e.g., x = 5;)
//   printStmt   -> "print" expression ";"     (e.g., print x;)
//   expression  -> term (("+" | "-") term)*   (addition and subtraction, left-associative)
//   term        -> factor (("*" | "/") factor)* (multiplication and division, left-associative)
//   factor      -> NUMBER | IDENTIFIER | "(" expression ")"  (numbers, variables, or grouped expressions)
//
// This grammar ensures proper operator precedence:
//   * and / bind tighter than + and -
//   All operators are left-associative (e.g., a - b - c = (a - b) - c)
class Parser {
public:
    // Constructor: takes the vector of tokens produced by the Lexer.
    explicit Parser(std::vector<Token> tokens);

    // Main parsing function: processes all tokens and returns the AST.
    // Returns a vector of statements (since our program can have multiple statements).
    std::vector<std::unique_ptr<Stmt>> parseProgram();

private:
    // The tokens we're parsing.
    std::vector<Token> tokens_;

    // Current position in the token stream.
    size_t pos_ = 0;

    // Helper functions for parsing (similar to those in the Lexer but for tokens)

    // Returns the current token without consuming it.
    const Token& peek() const;

    // Returns the most recently consumed token.
    const Token& previous() const;

    // Returns true if we've reached the end of the token stream.
    bool isAtEnd() const;

    // Returns true if the current token matches the given type (without consuming it).
    bool check(TokenType type) const;

    // Consumes and returns the current token.
    const Token& advance();

    // If the current token matches the given type, consumes it and returns true.
    // Otherwise, returns false without consuming anything.
    bool match(TokenType type);

    // Consumes the current token if it matches the expected type.
    // Throws an error with the given message if it doesn't match.
    const Token& expect(TokenType type, const std::string& errorMessage);

    // Parsing functions for different grammar rules (each returns a unique_ptr to the appropriate AST node)

    // Parses a statement (either assignment or print).
    std::unique_ptr<Stmt> parseStatement();

    // Parses an assignment statement (e.g., x = 5;).
    std::unique_ptr<Stmt> parseAssignStatement();

    // Parses a print statement (e.g., print x;).
    std::unique_ptr<Stmt> parsePrintStatement();

    // Parses an expression (handles addition and subtraction).
    std::unique_ptr<Expr> parseExpression();

    // Parses a term (handles multiplication and division).
    std::unique_ptr<Expr> parseTerm();

    // Parses a factor (handles numbers, variables, and parentheses).
    std::unique_ptr<Expr> parseFactor();
};