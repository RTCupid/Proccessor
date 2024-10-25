#ifndef PROCCESSOR
    #define PROCCESSOR
    #include <sys/types.h>

    #include "Stack/Stack.cpp"
    #include "Stack/Stack_Error_Checking.cpp"

    //TODO: more structures and enums and arrays of structures

    enum REG_t {
        AX = 0,
        BX = 1,
        CX,
        DX
    };

    typedef struct {
        int* code;
        int  size;
        int  ip;
    } proc_t;

    const size_t nregisters = 4;
    const size_t nRAM = 100;
    const size_t capacity_code = 200;

    void SPU (stack_t* STK, proc_t* PRC, int* REG, int* RAM);

    void MakeProgrammCode (proc_t* PRC);

    void PrDump (stack_t STK, proc_t PRC, int* REG);

    void DumpRAM (int* RAM);

    int GetArgPush (proc_t* PRC, int* REG, int* RAM);

    int* GetArgPop (proc_t* PRC, int* REG, int* RAM);

#endif
