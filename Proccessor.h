#ifndef PROCCESSOR
    #define PROCCESSOR
    #include <sys/types.h>
    enum cmd_t {
        Push = 1,                                          // change to CMD.PUSH etc
        Add = 2,
        Sub = 3,
        Div = 4,
        Mul = 5,
        Out = 6,
        Hlt = -1
    };

    enum REG_t {
        AX = 0,
        BX = 1,
        CX,
        DX
    };

    const size_t start_capacity = 10;
#endif
