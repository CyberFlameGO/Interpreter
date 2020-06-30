//
// Created by George on 30-Jun-20.
//

#ifndef TWITCHINTERPRETER_TOKEN_H
#define TWITCHINTERPRETER_TOKEN_H

typedef struct _token_t {
    char* type;
    char* literal;
} Token;

//general file stuff
const char* ILLEGAL_TOKEN = "ILLEGAL_TOKEN";
const char* EOF = "EOF"; //end of file
const char* IDENT = "IDENT";
const char* _INT = "INT";
const char* STRING = "STRING";

//operators
const char* ASSIGN = "=";
const char* PLUS = "+";
const char* MINUS = "-";
const char* BANG = "!";
const char* ASTERISK = "*";
const char* SLASH = "/";
const char* LT = "<";
const char* GT = ">";
const char* EQ = "==";
const char* NOT_EQ = "!=";

//delimiters
const char* COMMA = ",";
const char* SEMICOLON = ";";
const char* LPAREN = "(";
const char* RPAREN = ")";
const char* LBRACE = "{";
const char* RBRACE = "}";
const char* LBRACKET = "[";
const char* RBRACKET = "]";

//keywords
const char* FUNCTION = "FUNC";
const char* LET = "LET";
const char* _TRUE = "TRUE";
const char* _FALSE = "FALSE";
const char* IF = "IF";
const char* ELSE = "ELSE";
const char* RETURN = "RETURN";

#endif //TWITCHINTERPRETER_TOKEN_H
