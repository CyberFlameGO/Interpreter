//
// Created by George on 01-Jul-20.
//

#ifndef TWITCHINTERPRETER_PARSER_H
#define TWITCHINTERPRETER_PARSER_H

#include "lexer.h"
#include "token.h"
#include "hashmap.h"

typedef struct Parser_t {
    Lexer lexer;
    Token currentToken;
    Token peekToken;

    //used to check when parsing a function
    //or associated functions
    map_t prefixParserFns;
    map_t infixParserFns;
    char* errors[];

} Parser;

#endif //TWITCHINTERPRETER_PARSER_H
