//#include "Stack\Stack.h"
//#include "Stack\Config.h"
#ifndef ASSEMBLER
    #define ASSEMBLER

    #include "Stack/Stack.cpp"
    #include "Stack/Stack_Error_Checking.cpp"

    enum cmd_t {
        CMD_PUSH = 17,                                          // change to CMD_PUSH etc
        CMD_PUSH_REG = 33,
        CMD_PUSH_RAM = 49,
        CMD_ADD = 2,
        CMD_SUB = 3,
        CMD_DIV = 4,
        CMD_MUL = 5,
        CMD_OUT = 6,
        CMD_POP_REG = 7,
        CMD_JMP = 8,
        CMD_JA = 9,
        CMD_POP_RAM = 10,
        CMD_HLT = -1
    };

    typedef struct {
        char name[20];
        int addr;
    } label_t;

    typedef struct {
        int addr;
        char name[20];
    } fixup_t;

    const size_t capacity_code = 20;
    const size_t capacity_labels = 10;
    const size_t capacity_fixup = 10;

    const size_t max_len_cmd = 20;
#endif

