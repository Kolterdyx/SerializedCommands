//
// Created by kolterdyx on 21/08/23.
//

#include "CommandParser.h"

CommandStatus CommandParser::parse(uint8_t *rawCommand, ParsedCommand *parsedCommand) {
    // First two bytes are the command
    uint16_t command = (rawCommand[0] << 8) | rawCommand[1];
    parsedCommand->command = command;
    for (int i = 0; i < commandCount; i++) {
        if (commands[i].command == command) {
            uint8_t argCount = commands[i].argCount;
            uint8_t argLengths[argCount];
            uint8_t argLength = 0;
            for (int j = 0; j < argCount; j++) {
                argLength += commands[i].argLengths[j];
                argLengths[j] = commands[i].argLengths[j];
            }
            // Third byte is the byte length of the command
            if (argLength + 3 != rawCommand[2]) {
                return CORRUPTED;
            }
            // Everything else are the arguments in the following format:
            // [type, length, value][type, length, value][type, length, value]...
            // the type is one byte, the length is one byte and the value is the length of the length byte
            uint8_t *argStart = rawCommand + 3;
            CommandArg *args = new CommandArg[argCount];
            for (int j = 0; j < argCount; j++) {
                args[j].type = commands[i].argTypes[j];
                args[j].arg = new uint8_t[argLengths[j]];
                memcpy(args[j].arg, argStart, argLengths[j]);
                argStart += argLengths[j];
            }
            parsedCommand->args = args;
            auto result = commands[i].handler(parsedCommand);
            for (int j = 0; j < argCount; j++) {
                delete[] args[j].arg;
            }
            delete[] args;
            return result;
        }
    }
    return UNKNOWN;
}

bool CommandParser::registerCommand(
        uint16_t command,
        CommandArgType *argTypes,
        uint8_t argCount,
        uint8_t *argLengths,
        CommandHandler handler) {
    if (commandCount < 16 && !this->exists(command)) {
        commands[commandCount].command = command;
        commands[commandCount].argTypes = argTypes;
        commands[commandCount].argCount = argCount;
        commands[commandCount].argLengths = argLengths;
        commands[commandCount].handler = handler;
        commandCount++;
        return true;
    }
    return false;
}

bool CommandParser::exists(uint16_t command) {
    for (int i = 0; i < commandCount; i++) {
        if (commands[i].command == command) {
            return true;
        }
    }
    return false;
}
