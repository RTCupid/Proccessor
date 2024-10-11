#ifndef PROCCESSOR
    #define PROCCESSOR
    #include <sys/types.h>
    enum cmd_t {
        Push = 1,
        Add = 2,
        Sub = 3,
        Div = 4,
        Mul = 5,
        Out = 6,
        Hlt = -1
    };

    const size_t start_capacity = 10;
#endif
