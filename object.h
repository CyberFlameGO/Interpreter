//
// Created by George on 30-Jun-20.
//


#include <stdbool.h>
#include <windef.h>

#ifndef TWITCHINTERPRETER_OBJECT_H
#define TWITCHINTERPRETER_OBJECT_H


typedef struct String_t {
    char* value;
} String;

typedef struct Error_t {
    char* message;
} Error;

typedef struct Integer_t {
    int value;
} Integer;

typedef struct Boolean_t {
    BOOL value;
} Boolean;

typedef struct Return_t {
    char* value;
} Return;

#endif //TWITCHINTERPRETER_OBJECT_H
