#ifndef PROCCESSOR
    #define PROCCESSOR
    #include <sys/types.h>
    enum cmd_t {
        Push = 1,
        Add = 2,
        Sub = 3,
        Out = 4,
        Div = 5,
        Hlt = -1
    };

    const size_t start_capacity = 10;
#endif
