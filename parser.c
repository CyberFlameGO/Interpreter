//
// Created by George on 02-Jul-20.
//

#include "parser.h"
#include "ast.h"

Parser parser;

void init_precedence_map(void) {
    precedences = hashmap_new();
    hashmap_put(precedences, EQ, PRECEDENCE_EQUAL);
    hashmap_put(precedences, NOT_EQ, PRECEDENCE_EQUAL);
    hashmap_put(precedences, LT, PRECEDENCE_LESS_GREATER);
    hashmap_put(precedences, GT, PRECEDENCE_LESS_GREATER);
    hashmap_put(precedences, PLUS, PRECEDENCE_SUM);
    hashmap_put(precedences, MINUS, PRECEDENCE_SUM);
    hashmap_put(precedences, SLASH, PRECEDENCE_PRODUCT);
    hashmap_put(precedences, ASTERISK, PRECEDENCE_PRODUCT);
    hashmap_put(precedences, LPAREN, PRECEDENCE_CALL);
}

int peekPrecedence(void) {
    if((char *) hashmap_get(precedences, parser.currentToken, (any_t *) parser.peekToken) == parser.peekToken) {
        return PRECEDENCE_EQUAL;
    }
    return PRECEDENCE_LOWEST;
}

int curPrecedence(void) {
    if((char *) hashmap_get(precedences, parser.currentToken, (any_t *) parser.currentToken) == parser.peekToken) {
        return PRECEDENCE_EQUAL;
    }
    return PRECEDENCE_LOWEST;
}

InfixExpression parseInfixExpression(Expression left) {
    InfixExpression expression;

    expression.token = parser.currentToken;
    expression.oper = parser.peekToken;
    expression.left = left;

    int precedence = peekPrecedence();
    nextToken();
    expression.right = parseExpression(precedence);

    return expression;
}

void nextParserToken(void) {
    parser.currentToken = nextToken().type;
    parser.peekToken = nextToken().literal;
}

Program parseProgram(void) {
    Program program;
    Statement statement;
    int position = 0;

    if (program.statements[position].node.string != NULL && program.statements[position].node.tokenLiteral != NULL) {
        program.statements[position] = statement;
        position++;
    }
    while(parser.currentToken != EOF) {
        parseStatement();

        Statement stmt = parseStatement();

        if(stmt.node.string != NULL && stmt.node.tokenLiteral != NULL) {
            program.statements[0] = stmt;
        }
        nextParserToken();
    }
}

IntegerLiteral parseIntegerLiteral(void) {
    IntegerLiteral lit;
    int value = parser.currentToken;

    if(value != NULL) {
        lit.value = value;
    }
    return lit;
}

Statement parseStatement(void) {

    Statement statement;

    if (parser.currentToken == LET) {
        LetStatement let;
        let.token.type = parser.currentToken;
        if (expectPeek(IDENT)) {
            statement.node.tokenLiteral = NULL;
            statement.node.string = NULL;
            return statement;
        } else {
            statement.node.tokenLiteral = let.token.literal;
            statement.node.string = let.token.type;
            return statement;
        }
    } else if (parser.currentToken == RETURN) {
        ReturnStatement ret;
        nextParserToken();

        if(curTokenIs(SEMICOLON)) {
            nextParserToken();
        }

        statement.node.string = ret.token.type;
        statement.node.tokenLiteral = ret.token.literal;
        return statement;
    } else {
        ExpressionStatement expressionStatement;
        expressionStatement.expression = parseExpression(PRECEDENCE_LOWEST);

        if(peekTokenIs(SEMICOLON)) {
            nextParserToken();
            statement.node.tokenLiteral = expressionStatement.expression.Node.tokenLiteral;
            statement.node.string = expressionStatement.expression.Node.string;
            return statement;
        }
    }
    return statement;
}

Expression parseExpression(int precedence) {
    Expression expression;

    //todo prefix

    if (peekTokenIs(SEMICOLON) && precedence < peekPrecedence()) {
        nextParserToken();
        //todo infix
    }

    return expression;
}

bool curTokenIs(char *token) {
    return parser.peekToken == token;
}

