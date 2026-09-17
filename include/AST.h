#pragma once
#include <string>
#include <memory>

// This file defines the Abstract Syntax Tree (AST) nodes for our Mini-like language.
// The AST represents the structure of the source code after parsing.

// Enumeration of expression types.
enum class ExprType
{
    NUMBER,      // A numeric literal (e.g., 42, 3.14)
    VARIABLE,    // A variable identifier (e.g., x, count)
    BINARY       // A binary operation (e.g., x + y, 2 * 3)
};

// Base class for all expression nodes.
struct Expr
{
    ExprType type; // The type of this expression.
    virtual ~Expr() = default; // Virtual destructor for safe polymorphic deletion.

protected:
    // Constructor is protected because we don't instantiate Expr directly.
    explicit Expr(ExprType t) : type(t) {}
};

// Represents a numeric literal expression.
struct NumberExpr : Expr
{
    double value; // The numeric value (e.g., 42.0, 3.14).

    // Constructor initializes the base class as NUMBER and stores the value.
    explicit NumberExpr(double val) : Expr(ExprType::NUMBER), value(val) {}
};

// Represents a variable expression (e.g., x, total).
struct VariableExpr : Expr
{
    std::string name; // The name of the variable (e.g., "x").

    // Constructor initializes the base class as VARIABLE and stores the name.
    explicit VariableExpr(std::string n) : Expr(ExprType::VARIABLE), name(std::move(n)) {}
};

// Represents a binary operation expression (e.g., a + b, x * y).
struct BinaryExpr : Expr
{
    char op;           // The operator character (e.g., '+', '-', '*', '/').
    std::unique_ptr<Expr> left;  // Pointer to the left-hand side expression.
    std::unique_ptr<Expr> right; // Pointer to the right-hand side expression.

    // Constructor initializes the base class as BINARY and stores the operator and sub-expressions.
    BinaryExpr(char o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : Expr(ExprType::BINARY), op(o), left(std::move(l)), right(std::move(r)) {}
};

//-------- statements

// Enumeration of statement types.
enum class StmtType { ASSIGN, PRINT };

// Base class for all statement nodes.
struct Stmt
{
    StmtType type; // The type of this statement.
    virtual ~Stmt() = default; // Virtual destructor for safe polymorphic deletion.

protected:
    // Constructor is protected because we don't instantiate Stmt directly.
    explicit Stmt(StmtType t) : type(t) {}
};

// Represents an assignment statement (e.g., x = 42;).
struct AssignStmt : Stmt
{
    std::string name;           // The name of the variable being assigned to.
    std::unique_ptr<Expr> value; // Pointer to the expression whose value is being assigned.

    // Constructor initializes the base class as ASSIGN and stores the variable name and value expression.
    AssignStmt(std::string n, std::unique_ptr<Expr> v)
        : Stmt(StmtType::ASSIGN), name(std::move(n)), value(std::move(v)) {}
};

// Represents a print statement (e.g., print x;).
struct PrintStmt : Stmt
{
    std::unique_ptr<Expr> value; // Pointer to the expression whose value is to be printed.

    // Constructor initializes the base class as PRINT and stores the expression to print.
    explicit PrintStmt(std::unique_ptr<Expr> v) : Stmt(StmtType::PRINT), value(std::move(v)) {}
};