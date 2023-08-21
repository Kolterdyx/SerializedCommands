//
// Created by kolterdyx on 21/08/23.
//

#ifndef ARDUINOANTENNAALIGNER_COMMANDBUILDER_H
#define ARDUINOANTENNAALIGNER_COMMANDBUILDER_H

#include "Command.h"
#include <Arduino.h>

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
            memcpy(this->args[this->argCount], &arg, sizeof(arg));
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


#endif //ARDUINOANTENNAALIGNER_COMMANDBUILDER_H
