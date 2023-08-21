#ifndef ARDUINOANTENNAALIGNER_COMMANDPARSER_H
#define ARDUINOANTENNAALIGNER_COMMANDPARSER_H

#include "Arduino.h"
#include "Command.h"

class CommandParser {
private:

    Command commands[16]{};
    uint8_t commandCount = 0;

    bool exists(uint16_t command);

public:
    CommandStatus parse(uint8_t *rawCommand, ParsedCommand *parsedCommand);

    bool registerCommand(uint16_t command, CommandArgType *argTypes, uint8_t argCount, uint8_t *argLengths, CommandHandler handler);
};

#endif //ARDUINOANTENNAALIGNER_COMMANDPARSER_H
