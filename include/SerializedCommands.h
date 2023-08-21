//
// Created by kolterdyx on 21/08/23.
//

#ifndef ARDUINOANTENNAALIGNER_SERIALIZEDCOMMANDS_H
#define ARDUINOANTENNAALIGNER_SERIALIZEDCOMMANDS_H

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


class CommandParser {
private:

    Command commands[16]{};
    uint8_t commandCount = 0;

    bool exists(uint16_t command);

public:
    CommandStatus parse(uint8_t *rawCommand, ParsedCommand *parsedCommand);

    bool registerCommand(uint16_t command, CommandArgType *argTypes, uint8_t argCount, uint8_t *argLengths, CommandHandler handler);
};

class CommandBuilder {
public:
    CommandBuilder &make(uint16_t command);

    CommandBuilder &arg(CommandArgType type, uint8_t *arg);

    CommandBuilder &arg(CommandArgType type, uint8_t *arg, uint8_t length);

    CommandBuilder &handler(CommandHandler handler);

    Command build();

private:
    Command command;
    uint8_t argCount = 0;
    uint8_t argLengths[16]{};
    CommandArgType argTypes[16]{};
    uint8_t *args[16]{};
};

#endif //ARDUINOANTENNAALIGNER_SERIALIZEDCOMMANDS_H
