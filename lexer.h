//
// Created by George on 30-Jun-20.
//

#ifndef TWITCHINTERPRETER_LEXER_H
#define TWITCHINTERPRETER_LEXER_H

#include <rpcndr.h>
#include <windef.h>
#include "token.h"

typedef struct Lexer_t {
    char* input;
    int position, readPosition;
    char ch;
} Lexer;

//skip whitespace because it doesn't need to be read
void skipWhitespace();
BOOL isDigit(char ch);
Token newToken(char* token, char ch);
BOOL isCharacter(char ch);
void readChar();
char* peekChar();
char* readIdentifier();
char* readNumber();
char* readString();
Lexer newLexer(char* input);
Token nextToken();

#endif //TWITCHINTERPRETER_LEXER_H
