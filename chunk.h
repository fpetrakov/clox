#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_NEGATE,
    OP_ADD,
    OP_SUBSTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN,
} OpCode;

typedef struct {
    uint32_t line;
    uint32_t count;
} LineRun;

typedef struct {
    uint32_t count;
    uint32_t capacity;
    uint8_t* code;

    uint32_t lineCount;
    uint32_t lineCapacity;
    LineRun* lines;

    ValueArray constants;
} Chunk;

uint32_t getLine(Chunk*, uint32_t instruction);
void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, uint32_t line);
void freeChunk(Chunk* chunk);
uint32_t addConstant(Chunk* chunk, Value value);

#endif
