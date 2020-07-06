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
    return parser.currentToken == token;
}

bool peekTokenIs(char* token) {
    return parser.peekToken == token;
}

bool expectPeek(char* token) {
    if( peekTokenIs(token)) {
        nextParserToken();
        return true;
    } else {
        return false;
    }
}

ArrayLiteral parseArrayLiteral(void) {
    ArrayLiteral lit;
    int position = 0;
    if (lit.elements[position].Node.tokenLiteral != NULL && lit.elements[position].Node.string != NULL) {
        lit.elements[position].Node.tokenLiteral = parseExpressionList(RBRACKET);
        lit.elements[position].Node.string = parser.currentToken;
        position++;
    }
    return lit;
}

map_t parseExpressionList(char* end) {
    map_t expressionListMap = hashmap_new();

    if (peekTokenIs(end)) {
        nextParserToken();
        return expressionListMap;
    } else {

        hashmap_put(expressionListMap, "PREC", PRECEDENCE_LOWEST);

        nextParserToken();
        while (peekTokenIs(COMMA)) {
            nextParserToken();
            nextParserToken();
            hashmap_put(expressionListMap, "PREC", PRECEDENCE_LOWEST);
        }

        if (!expectPeek(end)) {
            parseExpressionList(end);
        }
    }
    return expressionListMap;
}

StringLiteral parseStringLiteral(void) {
    StringLiteral lit;
    lit.token.type = parser.currentToken;
    lit.value = parser.peekToken;
    return lit;
}

CallExpression parseCallExpression(any_t function) {
    CallExpression exp;
    int position = 0;
    if(exp.arguments[position].Node.string != NULL && exp.arguments[position].Node.tokenLiteral != NULL) {
        exp.arguments[position].Node.tokenLiteral = parseExpressionList(RPAREN);
        exp.arguments[position].Node.string = parser.currentToken;
        position++;
    }
    return exp;
}

map_t parseCallArguments(void) {
    map_t args = hashmap_new();

    if (peekTokenIs(RPAREN)) {
        nextParserToken();
        return args;
    }

    nextParserToken();
    hashmap_put(args, "PREC", PRECEDENCE_LOWEST);

    while (peekTokenIs(COMMA)) {
        nextParserToken();
        nextParserToken();
        hashmap_put(args, "PREC", PRECEDENCE_LOWEST);
    }
    if (!expectPeek(RPAREN)) {
        return NULL;
    }

    return args;
}

FunctionLiteral parseFunctionLiteral(void) {
    FunctionLiteral lit;

    if (peekTokenIs(RPAREN)) {
        nextParserToken();
        return lit;
    } else {
        int position = 0;
        if (lit.parameters[0] != NULL) {
            lit.parameters[0] = parseFunctionParameters();
            position++;
        }
    }
    if (!expectPeek(LBRACE)) {
        return lit;
    }
    lit.body = parseBlockStatement();
    return lit;
}

map_t parseFunctionParameters(void) {
    map_t params = hashmap_new();

    if (peekTokenIs(RPAREN)) {
        nextParserToken();
        return params;
    }

    nextParserToken();
    hashmap_put(params, "TOK", parser.currentToken);

    while (peekTokenIs(COMMA)) {
        nextParserToken();
        nextParserToken();
        hashmap_put(params, "TOK", parser.currentToken);
    }

    if (!peekTokenIs(RPAREN)) {
        return NULL;
    }
    return params;
}

IfExpression parseIfExpression(void) {
    IfExpression ife;

    if (expectPeek(LPAREN)) {
        ife.token.type = "";
        ife.token.literal = "";
        ife.condition.Node.tokenLiteral = "";
        ife.condition.Node.string = "";
        return ife;
    }
    nextParserToken();
    ife.condition.Node.tokenLiteral = parseExpressionList(PRECEDENCE_LOWEST);
    ife.condition.Node.string = parseExpressionList(PRECEDENCE_LOWEST);

    if (!expectPeek(RPAREN)) {
        ife.token.type = "";
        ife.token.literal = "";
        ife.condition.Node.tokenLiteral = "";
        ife.condition.Node.string = "";
        return ife;
    }

    if (!expectPeek(LBRACE)) {
        ife.token.type = "";
        ife.token.literal = "";
        ife.condition.Node.tokenLiteral = "";
        ife.condition.Node.string = "";
        return ife;
    }
    ife.consequence = parseBlockStatement();
    return ife;
}

BlockStatement parseBlockStatement(void) {
    BlockStatement blockStatement;

    {
        nextParserToken();
    }

    while (!curTokenIs(RBRACE) && !curTokenIs(EOF)) {
        int position = 0;
        if(blockStatement.statements[position].node.tokenLiteral != NULL && blockStatement.statements[position].node.string != NULL) {
            blockStatement.statements[position] = parseStatement();
            position++;
        }
        nextParserToken();
    }
    return blockStatement;
}

Expression parseGroupExpression(void) {
    Expression exp;
    nextParserToken();

    if (!expectPeek(RPAREN)) {
        exp.Node.string = "";
        exp.Node.tokenLiteral = "";
        return exp;
    } else {
        exp = parseExpression(RPAREN);
    }
    return exp;
}

Boolean parseBoolean(void) {
    Boolean b;
    b.token.type = parser.currentToken;
    b.value = parser.currentToken;
    b.token.literal = parser.peekToken;
    return b;
}

PrefixExpression parsePrefixExpression(void) {
    PrefixExpression exp;

    exp.token.literal = parser.currentToken;
    exp.token.type = parser.peekToken;
    exp.operator = parser.currentToken + 1;

    nextParserToken();
    exp.right = parseExpression(PRECEDENCE_PREFIX);
    return exp;
}

Identifier parseIdentifier(void) {
    Identifier ident;
    ident.token.literal = parser.currentToken;
    ident.token.type = parser.currentToken;
    ident.value = parser.peekToken;
    return ident;
}

LetStatement parseLetStatement(void) {
    LetStatement stmt;
    if (!expectPeek(IDENT)) {
        stmt.value.value = "";
        stmt.value.token.type = "";
        stmt.value.token.literal = "";
        stmt.value.value = "";
        stmt.token.literal = "";
        stmt.token.type = "";
        stmt.name.token.type = "";
        stmt.name.token.literal = "";
        stmt.name.value = "";
        return stmt;
    }
    stmt.name.value = parser.currentToken;
    stmt.name.token.literal = parser.currentToken;
    stmt.name.token.type = parser.peekToken;

    if (!expectPeek(ASSIGN)) {
        stmt.value.value = "";
        stmt.value.token.type = "";
        stmt.value.token.literal = "";
        stmt.value.value = "";
        stmt.token.literal = "";
        stmt.token.type = "";
        stmt.name.token.type = "";
        stmt.name.token.literal = "";
        stmt.name.value = "";
        return stmt;
    }

    nextParserToken();
    return stmt;
}

ReturnStatement parseReturnStatement(void) {
    ReturnStatement rtrn;
    nextParserToken();
    rtrn.value = parseExpression(PRECEDENCE_LOWEST);

    if (peekTokenIs(SEMICOLON)) {
        nextParserToken();
    }
    return rtrn;
}

