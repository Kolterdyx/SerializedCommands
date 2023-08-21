//
// Created by kolterdyx on 21/08/23.
//

#include "CommandBuilder.h"

CommandBuilder::CommandBuilder(uint16_t command) {
    this->command = command;
}


uint8_t *CommandBuilder::build() {
    auto rawCommand = new uint8_t[calcRawCommandLength()];

    rawCommand[0] = this->command >> 8;
    rawCommand[1] = this->command & 0xFF;
    rawCommand[2] = 3;
    for (int i = 0; i < this->argCount; i++) {
        rawCommand[2] += this->argLengths[i];
    }
    uint8_t *argStart = rawCommand + 3;
    for (int i = 0; i < this->argCount; i++) {
        memcpy(argStart, this->args[i], this->argLengths[i]);
        argStart += this->argLengths[i];
    }
    return rawCommand;
}

uint16_t CommandBuilder::calcRawCommandLength() {
    uint16_t length = 3;
    for (int i = 0; i < this->argCount; i++) {
        length += this->argLengths[i];
    }
    return length;
}
