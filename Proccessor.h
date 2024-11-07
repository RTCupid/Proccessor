#ifndef PROCCESSOR
    #define PROCCESSOR
    #include <sys/types.h>

    #include "Stack/Config.h"
    #include "Stack/Stack.h"

    //TODO: more structures and enums and arrays of structures

    enum mask_t
    {
        MASK_NUM = 1,
        MASK_REG = 2,
        MASK_RAM = 4,
    };

    enum REG_t
    {
        AX = 0,
        BX = 1,
        CX = 2,
        DX = 3,
        EX = 4,
    };

    typedef struct
    {
        int* REG;
        int* RAM;
        int* code;
        stack_t AddrRet;
        int  size;
        int  ip;
    } proc_t;

    const size_t nregisters = 5;
    const size_t nRAM = 10000;
    const size_t capacity_code = 200;

    void PrcCtor (proc_t* PRC);

    void PrcDtor (proc_t* PRC);

    void SPU (stack_t* STK, proc_t* PRC);

    void MakeProgrammCode (proc_t* PRC);

    void PrDump (stack_t STK, proc_t PRC);

    void DumpRAM (int* RAM);

    int GetArgPush (proc_t* PRC, int* REG, int* RAM);

    int* GetArgPop (proc_t* PRC, int* REG, int* RAM);

#endif
