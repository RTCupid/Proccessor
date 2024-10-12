#ifndef PROCCESSOR
    #define PROCCESSOR
    #include <sys/types.h>
    enum cmd_t {
        CMD_PUSH = 1,                                          // change to CMD_PUSH etc
        CMD_PUSH_REG = 33,
        CMD_ADD = 2,
        CMD_SUB = 3,
        CMD_DIV = 4,
        CMD_MUL = 5,
        CMD_OUT = 6,
        CMD_POP = 7,
        CMD_HLT = -1
    };

    enum REG_t {
        AX = 0,
        BX = 1,
        CX,
        DX
    };

    const size_t start_capacity = 10;
#endif
