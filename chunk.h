#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_NEGATE,
    OP_PRINT,
    OP_POP,
    OP_GET_GLOBAL,
    OP_DEFINE_GLOBAL,
    OP_SET_GLOBAL,
    OP_ADD,
    OP_SUBSTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_CONSTANT,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_CONSTANT_LONG,
    OP_RETURN,
} OpCode;

typedef struct {
    int line;
    int count;
} LineRun;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;

    int lineCount;
    int lineCapacity;
    LineRun* lines;

    ValueArray constants;
} Chunk;

int getLine(Chunk*, int instruction);
void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);

#endif
