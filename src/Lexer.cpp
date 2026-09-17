#include "Lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(std::string source):source_(std::move(source)){}

bool Lexer::isAtEnd() const{
    return pos_ >= source_.size();
}

char Lexer::peek() const{
    if(isAtEnd()) return '\0';
    return source_[pos_];
}

char Lexer::peekNext() const{
    if(isAtEnd())return '\0';
    return source_[pos_+1];
}

char Lexer::advance(){
    char c = source_[pos_++];
    if(c == '\n')line_++;
    return c;
}

void Lexer::skipWhitespaceAndComments(){
    while(!isAtEnd()){
        char c = peek();
        if(c == ' ' || c == '\t' || c == '\r' || c == '\n'){
            advance();
        }else if(c == '/' && peekNext() == '/'){
            while(!isAtEnd() && peek() != '\n') advance();
        }else{
            break;
        }
    }
}


Token Lexer:: makeToken(TokenType type, const std::string& lexeme){
    return Token{type,lexeme,0.0,line_};
}

Token Lexer::scanNumber(){
    size_t start = pos_;
    while(!isAtEnd() && std::isdigit(peek()))advance();

    if(peek() == '.' && std::isdigit(peek())){
        advance();
        while(!isAtEnd() && std::isdigit(peek()))advance();
    }

    std::string text = source_.substr(start,pos_-start);
    Token tok = makeToken(TokenType::NUMBER , text);
    tok.numberValue = std::stod(text);
    return tok;
}


Token Lexer::scanIdentifierOrKeyword(){
    size_t start = pos_;
    
    while(!isAtEnd() && (std::isalnum(peek()) || peek() == '_'))advance();

    std::string text = source_.substr(start,pos_-start);
    if(text == "print"){
        return makeToken(TokenType::PRINT,text);
    }

    return makeToken(TokenType::IDENTIFIER,text);
}


std:: vector<Token> Lexer::tokenize(){
    std::vector<Token>tokens;

    while(true){
        skipWhitespaceAndComments();
        if(isAtEnd())break;


        char c = peek();

        if(std::isdigit(c)){
            tokens.push_back(scanNumber());
            continue;
        }

        if(std::isalpha(c) || c == '_'){
            tokens.push_back(scanIdentifierOrKeyword());
            continue;
        }

        advance();


        switch (c) {
            case '+': tokens.push_back(makeToken(TokenType::PLUS, "+")); break;
            case '-': tokens.push_back(makeToken(TokenType::MINUS, "-")); break;
            case '*': tokens.push_back(makeToken(TokenType::STAR, "*")); break;
            case '/': tokens.push_back(makeToken(TokenType::SLASH, "/")); break;
            case '=': tokens.push_back(makeToken(TokenType::EQUAL, "=")); break;
            case ';': tokens.push_back(makeToken(TokenType::SEMICOLON, ";")); break;
            case '(': tokens.push_back(makeToken(TokenType::LPAREN, "(")); break;
            case ')': tokens.push_back(makeToken(TokenType::RPAREN, ")")); break;
            default:
                throw std::runtime_error(
                    "Lexer error on line " + std::to_string(line_) +
                    ": unexpected character '" + std::string(1, c) + "'");
        }
    }

    tokens.push_back(Token{TokenType::END_OF_FILE, "", 0.0, line_});
    return tokens;
}