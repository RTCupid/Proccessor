#ifndef ENUM_H
#define ENUM_H
    #define DEF_CMD_(cmd, id, ...)\
            CMD_##cmd = id,

    enum cmd_t
    {
        CMD_LABEL = 0,
        #include "Commands.h"
        CMD_EOF = -2,
    };
    #undef DEF_CMD_
#endif /* ENUM_H */
