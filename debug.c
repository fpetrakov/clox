#include "chunk.h"
#include "stdio.h"

#include "debug.h"
#include "value.h"
#include <stdint.h>

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
};

static int constantLongInstruction(const char* name, Chunk* chunk, int offset) {
    uint32_t index = chunk->code[offset + 1]
        | (chunk->code[offset + 2] << 8)
        | (chunk->code[offset + 3] << 16);
    printf("%-16s %8d '", name, index);
    printValue(chunk->constants.values[index]);
    printf("'\n");
    return offset + 4;
};

int getLine(Chunk* chunk, int instruction) {
    int remaining = instruction;

    for (int i = 0; i < chunk->lineCount; i++) {
        if (remaining < chunk->lines[i].count) {
            return chunk->lines[i].line;
        }
        remaining -= chunk->lines[i].count;
    }

    return -1;
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    if (offset > 0 && (getLine(chunk, offset) == getLine(chunk, offset - 1))) {
        printf("   | ");
    } else {
        printf("%4d ", getLine(chunk, offset));
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT_LONG:
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
