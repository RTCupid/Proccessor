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
const size_t Capacity_code = 1000;

void PrcCtor (proc_t* PRC);

void PrcDtor (proc_t* PRC);

void SPU (stack_t* STK, proc_t* PRC, char* code_file);

void MakeProgrammCode (proc_t* PRC, char* code_file);

void PrDump     (stack_t STK, proc_t PRC);

void DumpRAM    (int* RAM);

int  GetArgPush (proc_t* PRC, int* REG, int* RAM);

int* GetArgPop  (proc_t* PRC, int* REG, int* RAM);

void RunPush    (proc_t* PRC, stack_t* STK);

void RunPop     (proc_t* PRC, stack_t* STK);

void RunAdd     (proc_t* PRC, stack_t* STK);

void RunSub     (proc_t* PRC, stack_t* STK);

void RunDiv     (proc_t* PRC, stack_t* STK);

void RunMul     (proc_t* PRC, stack_t* STK);

void RunOut     (proc_t* PRC, stack_t* STK);

void RunJmp     (proc_t* PRC);

void RunJa      (proc_t* PRC, stack_t* STK);

void RunJb      (proc_t* PRC, stack_t* STK);

void RunJe      (proc_t* PRC, stack_t* STK);

void RunJne      (proc_t* PRC, stack_t* STK);

void RunJae     (proc_t* PRC, stack_t* STK);

void RunSqrt    (proc_t* PRC, stack_t* STK);

void RunSin     (proc_t* PRC, stack_t* STK);

void RunCos     (proc_t* PRC, stack_t* STK);

void RunCall    (proc_t* PRC);

void RunRet     (proc_t* PRC);

void RunDraw    (proc_t* PRC);

void RunIn      (proc_t* PRC, stack_t* STK);

void RunMeow    (proc_t* PRC, stack_t* STK);

void RunHlt     (proc_t* PRC, int* next);

#endif
