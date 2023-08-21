//
// Created by kolterdyx on 21/08/23.
//

#ifndef ARDUINOANTENNAALIGNER_COMMAND_H
#define ARDUINOANTENNAALIGNER_COMMAND_H

#include <Arduino.h>

enum CommandStatus {
    OK,
    CORRUPTED,
    INVALID,
    UNKNOWN,
};

enum CommandArgType {
    INT,
    UINT,
    FLOAT,
    STRING,
};

struct CommandArg {
    CommandArgType type;
    uint8_t *arg;
};

struct ParsedCommand {
    uint16_t command;
    CommandArg *args;
};


typedef enum CommandStatus CommandStatus;
typedef enum CommandArgType CommandArgType;
typedef CommandStatus (*CommandHandler)(ParsedCommand *parsedCommand);

struct Command {
    uint16_t command;
    CommandArgType *argTypes;
    uint8_t argCount;
    uint8_t *argLengths;
    CommandHandler handler;
};


#endif //ARDUINOANTENNAALIGNER_COMMAND_H
