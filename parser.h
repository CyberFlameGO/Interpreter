//
// Created by George on 01-Jul-20.
//

#ifndef TWITCHINTERPRETER_PARSER_H
#define TWITCHINTERPRETER_PARSER_H

#include "lexer.h"
#include "token.h"
#include "hashmap.h"
#include "ast.h"

#include <stdbool.h>

typedef struct Parser_t {
    Lexer lexer;
    char *currentToken;
    char *peekToken;

    //used to check when parsing a function
    //or associated functions
    map_t prefixParserFns;
    map_t infixParserFns;
    char* errors[];

} Parser;

//represents the precedence order
const int PRECEDENCE_LOWEST = 0;
const int PRECEDENCE_EQUAL = 1;
const int PRECEDENCE_LESS_GREATER = 2;
const int PRECEDENCE_SUM = 3;
const int PRECEDENCE_PRODUCT = 4;
const int PRECEDENCE_PREFIX = 5;
const int PRECEDENCE_CALL = 6;

//help determine which order entities should be processed through the parser
map_t precedences;

void init_precedences_map(void);
int peekPrecedence(void);
int curPrecedence(void);
void registerPrefix(Token token, int function); //todo change this to accept the function
void registerInfix(Token token, int function);
InfixExpression parseInfixExpression(Expression left);
void nextParserToken(void);
Program parseProgram(void);
IntegerLiteral parseIntegerLiteral(void);
Statement parseStatement(void);
Expression parseExpression(int precedence); //^ refer to the precedence map
bool curTokenIs(char* token);
bool peekTokenIs(char* token);
bool expectPeek(char* token);
Parser newParser(Lexer lexer);
Expression parseArrayLiteral(void);
map_t parseExpressionList(char* end); //todo build map for this and return map
Expression parseStringLiteral(void);
Expression parseCallExpression(void);
map_t parseCallArguments(void);
Expression parseFunctionLiteral(void);
map_t parseFunctionParameters(void);
Expression parseIfExpression(void);
BlockStatement parseBlockStatement(void);
Expression parseGroupExpression(void);
Expression parseBoolean(void);
Expression parsePrefixExpression(void);
Expression parseIdentifier(void);
ReturnStatement parseReturnStatement(void);

#endif //TWITCHINTERPRETER_PARSER_H
