#ifndef ENUM
    #define ENUM
    enum cmd_t
    {
        CMD_PUSH = 17,                                          // change to CMD_PUSH etc
        CMD_PUSH_REG = 33,
        CMD_PUSH_RAM = 49,
        CMD_ADD = 2,
        CMD_SUB = 3,
        CMD_DIV = 4,
        CMD_MUL = 5,
        CMD_OUT = 6,
        CMD_POP = 7,
        CMD_JMP = 8,
        CMD_JA = 9,
        CMD_HLT = -1,
    };
#endif
