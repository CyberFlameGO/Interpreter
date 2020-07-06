//
// Created by George on 30-Jun-20.
//

#include <windef.h>
#include "token.h"

#ifndef TWITCHINTERPRETER_AST_H
#define TWITCHINTERPRETER_AST_H

typedef struct Node_t {
  char* tokenLiteral;
  char* string;
} Node;

typedef struct Statement_t {
    Node node;
} Statement;

typedef struct BlockStatement_t {
    Token token;
    Statement statements[];
} BlockStatement;


typedef struct Expression_t {
    Node Node;
} Expression;

typedef struct IndexExpression_t {
    Token token;
    Expression Left;
    Expression Right;
} IndexExpression;

typedef struct ArrayLiteral_t {
    Token token;
    Expression elements[];
} ArrayLiteral;


typedef struct Program_t {
    int dummy;
    Statement statements[]; //todo assignt his to memory and handle it properly;
} Program;

typedef struct Identifier_t {
    Token token;
    char* value;
} Identifier;


typedef struct Function_t {
    Token token;
    Identifier parameters[];
    //todo add in block statements
} Function;

typedef struct ReturnStatement_t {
    Token token;
    Expression value;
} ReturnStatement;


typedef struct ExpressionStatement_t {
    Token token;
    Expression expression;
} ExpressionStatement;

typedef struct LetStatement_t {
    Token token;
    Identifier name;
    Identifier value;
} LetStatement;

typedef struct IntegerLiteral_t {
    Token token;
    int value;
} IntegerLiteral;

typedef struct PrefixExpression_t {
    Token token;
    char* operator;
    Expression right;
} PrefixExpression;

typedef struct InfixExpression_t {
    char *token;
    Expression left;
    char* oper;
    Expression right;
} InfixExpression;

typedef struct Boolean_t {
    Token token;
    BOOL value;
} Boolean;

typedef struct IfExpression_t {
    Token token;
    Expression condition;
    BlockStatement consequence;
} IfExpression;


typedef struct FunctionLiteral_t {
    Token token;
    BlockStatement body;
    map_t parameters[];
} FunctionLiteral;

typedef struct CallExpression_t {
    Token token;
    any_t function;
    Expression arguments[];
} CallExpression;

typedef struct StringLiteral_t {
    Token token;
    char* value;
} StringLiteral;

#endif //TWITCHINTERPRETER_AST_H
