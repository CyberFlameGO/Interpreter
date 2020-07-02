//
// Created by George on 30-Jun-20.
//

#include "lexer.h"

Lexer lexer;
Token t;

Token nextToken() {
    
    skipWhitespace();

    switch (lexer.ch) {
        case '[':
            newToken(LBRACE, lexer.ch);
        case ']':
            newToken(LBRACE, lexer.ch);

        case '*':
            newToken(ASTERISK, lexer.ch);
        case '=':
        {
            if(peekChar() == '=') {
                readChar();
                newToken(EQ, lexer.ch);
            } else {
                newToken(ASSIGN, lexer.ch);
            }
        }

        case ';':
            newToken(SEMICOLON, lexer.ch);
        case '(':
            newToken(LBRACE, lexer.ch);
        case ')':
            newToken(RBRACE, lexer.ch);
        case ',':
            newToken(COMMA, lexer.ch);
        case '+':
            newToken(PLUS, lexer.ch);
        case '{':
            newToken(LBRACKET, lexer.ch);
        case '}':
            newToken(RBRACKET, lexer.ch);
        case '-':
            newToken(MINUS, lexer.ch);
        case '!':
        {
            if (peekChar() == '=') {
                readChar();
                newToken(NOT_EQ, lexer.ch);
            } else {
                newToken(BANG, lexer.ch);
            }
        }
        case '/':
            newToken(SLASH, lexer.ch);
        case '<':
            newToken(LT, lexer.ch);
        case '>':
            newToken(GT, lexer.ch);
        default:
            if(isCharacter(lexer.ch)) {
                t.literal = readIdentifier();
                //todo look up identifier
                return t;
            } else if(isDigit(lexer.ch)) {
                newToken(_INT, lexer.ch);
                t.literal = readNumber();
            } else {
                newToken(ILLEGAL_TOKEN, lexer.ch);
            }

    }
    return t;
}

Token newToken(char* token, char ch) {

    t.type = token;
    t.literal = &ch;
    return t;
}

Lexer newLexer(char* input) {
    lexer.input = input;
    return lexer;
}

void skipWhitespace() {
    if(lexer.ch == ' ' || lexer.ch == '\t' || lexer.ch == '\n' || lexer.ch == '\r')
        readChar();
}

bool isCharacter(char ch) {
    return 'a' <= ch && ch <= 'z' || 'A' <= ch && 'Z' <= ch || ch == "_";
}

void readChar() {
    if(lexer.readPosition >= sizeof(lexer.input)) {
        lexer.ch = 0;
    } else {
        lexer.ch = lexer.input[lexer.readPosition];
    }

    //refer to the lexer struct the position has to be replaced
    lexer.position = lexer.readPosition;
    lexer.readPosition += 1;
}

char* peekChar() {
    if (lexer.position >= sizeof(lexer.input))
        return "";
    return &lexer.input[lexer.position];
}

bool isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

char* readNumber() {
    if(isDigit(lexer.ch)) {
        readChar();
    }
    return &lexer.input[lexer.position];
}

char* readString() {
    while(lexer.ch != '*' || lexer.ch == 0) {
        readChar();
        if(lexer.ch == '*' || lexer.ch == 0)
            break;
    }
    return &lexer.input[lexer.position];
}