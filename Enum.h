#ifndef ENUM_H
#define ENUM_H
    #define DEF_CMD_(cmd, id, ...)\
            CMD_##cmd = id,

    enum cmd_t
    {
        #include "Commands.h"
    };
    #undef DEF_CMD_
#endif /* ENUM_H */



    /*enum cmd_t
    {
        CMD_PUSH = 1,                                          // change to CMD_PUSH etc
        CMD_POP = 2,
        CMD_ADD = 3,
        CMD_SUB = 4,
        CMD_DIV = 5,
        CMD_MUL = 6,
        CMD_OUT = 7,
        CMD_JMP = 8,
        CMD_JA = 9,
        CMD_COS = 10,
        CMD_SIN = 11,
        CMD_SQRT = 12,
        CMD_HLT = -1,
    };*/

        /*LABEL_ID = 0,
        PUSH_ID,
        POP_ID,
        ADD_ID,
        SUB_ID,
        DIV_ID,
        MUL_ID,
        OUT_ID,
        JMP_ID,
        JA_ID,
        HLT_ID,*/
