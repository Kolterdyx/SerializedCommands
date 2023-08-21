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
    explicit CommandBuilder(uint16_t command);

    template<typename T>
    CommandBuilder &arg(CommandArgType type, T arg, int pointer = 0) {
        this->argTypes[this->argCount] = type;
        this->argLengths[this->argCount] = sizeof(arg);
        if (pointer) {
            this->args[this->argCount] = new uint8_t[pointer * sizeof(arg[0])];
            memcpy(this->args[this->argCount], arg, pointer * sizeof(arg[0]));
        } else {
            this->args[this->argCount] = new uint8_t[sizeof(arg)];
            memcpy(this->args[this->argCount], reinterpret_cast<uint8_t *>(&arg), sizeof(arg));
        }
        this->argCount++;
        return *this;
    }

    uint8_t *build();

private:
    uint16_t command;
    uint8_t argCount = 0;
    uint8_t argLengths[16]{};
    CommandArgType argTypes[16]{};
    uint8_t *args[16]{};

    uint16_t calcRawCommandLength();
};

#endif //ARDUINOANTENNAALIGNER_SERIALIZEDCOMMANDS_H
