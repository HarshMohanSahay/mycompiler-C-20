#include "/home/professor/mystuffs/MyCompiler/include/Parser.h"
#include<stdexcept>

Parser::Parser(std::vector<Token>tokens):tokens_(std::move(tokens)){}

const Token& Parser::peek() const{return tokens_[pos_];}

const Token& Parser::previous() const{return tokens_[pos_-1];}

bool Parser::isAtEnd() const { return peek().type == TokenType::END_OF_FILE;}

bool Parser::check(TokenType type) const{return !isAtEnd() && peek().type == type;}

const Token& Parser::advance(){
    if(!isAtEnd())pos_++;
    return previous();
}

bool Parser::match(TokenType type){
    if(check(type)){
        advance();
        return true;
    }
    return false;
}


const Token& Parser::expect(TokenType type,const std::string& errorMessage){
    if(check(type))return advance();
    throw std::runtime_error(
        "parse error on line"+std::to_string(peek().line)+":"+errorMessage+"(got'"+peek().lexeme+"')"
    );
}

// program->statement*EOF

std::vector<std::unique_ptr<Stmt>> Parser::parseProgram(){
    std::vector<std::unique_ptr<Stmt>>statements;
    while(!isAtEnd()){
        statements.push_back(parseStatement());
    }
    return statements;
}


//statement -> assignStmt|printStmt
std::unique_ptr<Stmt>Parser::parseStatement(){
    if(check(TokenType::PRINT))return parsePrintStatement();
    if(check(TokenType::IDENTIFIER))return parseAssignStatement();

    throw std::runtime_error(
        "Parse error on line"+std::to_string(peek().line)+
        ":expected a statement,got'"+peek().lexeme + "'"
    );
}


//assignStmt -> identifier = ;
std::unique_ptr<Stmt>Parser::parseAssignStatement(){
    std::string name = advance().lexeme;
    expect(TokenType::EQUAL,"expected '=' after identifier");
    std::unique_ptr<Expr>value = parseExpression();
    expect(TokenType::SEMICOLON,"expected ';' after assignment");
    return std::make_unique<AssignStmt>(name,std::move(value));
}


//printStmt -> print expression ;
std::unique_ptr<Stmt>Parser::parsePrintStatement(){
    advance();
    std::unique_ptr<Expr>value = parseExpression();
    expect(TokenType::SEMICOLON,"expected ';' after print statement");
    return std::make_unique<PrintStmt>(std::move(value));
}


// expression ->term (("+" | "-")term)

std::unique_ptr<Expr>Parser::parseExpression(){
    std::unique_ptr<Expr> left = parseTerm();

    while(check(TokenType::PLUS) || check(TokenType::MINUS)){
        char op = advance().lexeme[0];
        std::unique_ptr<Expr>right = parseTerm();
        left = std::make_unique<BinaryExpr>(op,std::move(left),std::move(right));
    }
    return left;
}


// term -> factor (("*")| ("/"))

std::unique_ptr<Expr>Parser::parseTerm(){
    std::unique_ptr<Expr>left = parseFactor();

    while(check(TokenType::STAR) || check(TokenType::SLASH)){
        char op = advance().lexeme[0];
        std::unique_ptr<Expr> right = parseFactor();
        left = std::make_unique<BinaryExpr>(op,std::move(left),std::move(right));
    }
    return left;
}

//factor -> number / identifier / () expressions

std::unique_ptr<Expr>Parser::parseFactor(){
    if(check(TokenType::NUMBER)){
        double value = advance().numberValue;
        return std::make_unique<NumberExpr>(value);
    }


    if(check(TokenType::IDENTIFIER)){
        std::string name  = advance().lexeme;
        return std::make_unique<VariableExpr>(name);
    }

    if(match(TokenType::LPAREN)){
        std::unique_ptr<Expr> expr = parseExpression();
        expect(TokenType::RPAREN,"expected ')' after expression");
        return expr;
    }

    throw std::runtime_error(
        "Parse error on line "+std::to_string(peek().line)+
        ": expected a number , variable, or '(' , got '" + peek().lexeme + "'"
    );
}

