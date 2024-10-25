#ifndef ENUM
    #define ENUM
    #define DEF_CMD_(name, id, ...)\
            CMD_##name = id,

    enum cmd_t
    {
        DEF_CMD_(PUSH,   1,  true)
        DEF_CMD_( POP,   2,  true)
        DEF_CMD_( ADD,   3, false)
        DEF_CMD_( SUB,   4, false)
        DEF_CMD_( DIV,   5, false)
        DEF_CMD_( MUL,   6, false)
        DEF_CMD_( OUT,   7, false)
        DEF_CMD_( JMP,   8,  true)
        DEF_CMD_(  JA,   9,  true)
        DEF_CMD_( COS,  10, false)
        DEF_CMD_( SIN,  11, false)
        DEF_CMD_(SQRT,  12, false)
        DEF_CMD_( HLT,  -1, false)
    }
#endif



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
