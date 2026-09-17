#pragma once
#include <string>
#include <vector>
#include "Token.h"

// The Lexer (short for "Lexical Analyzer") is responsible for breaking down
// the source code into individual tokens - the basic building blocks of our language.
// Think of it like taking a sentence and splitting it into words and punctuation.

class Lexer
{
public:
    // Constructor: takes the source code as a string and prepares to tokenize it.
    explicit Lexer(std::string source);

    // Main method: converts the entire source code string into a vector of tokens.
    // This is where the lexical analysis happens.
    std::vector<Token> tokenize();

private:
    // The source code we're analyzing.
    std::string source_;

    // Current position in the source code (index of the next character to process).
    size_t pos_ = 0;

    // Current line number (helps with error reporting).
    int line_ = 1;

    // Returns true if we've reached the end of the source code.
    bool isAtEnd() const;

    // Returns the current character without consuming it.
    char peek() const;

    // Returns the next character without consuming it.
    char peekNext() const;

    // Consumes and returns the current character, then moves to the next one.
    char advance();

    // Skips over whitespace (spaces, tabs, newlines) and comments (// ...).
    void skipWhitespaceAndComments();

    // Scans a number token (handles both integers and floating-point numbers).
    Token scanNumber();

    // Scans an identifier or keyword (like variable names or the "print" keyword).
    Token scanIdentifierOrKeyword();

    // Helper function to create a token with the given type and lexeme.
    Token makeToken(TokenType type, const std::string& lexeme);
};