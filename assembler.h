//#include "Stack\Stack.h"
//#include "Stack\Config.h"
#ifndef ASSEMBLER
    #define ASSEMBLER

    #include "Stack/Stack.cpp"
    #include "Stack/Stack_Error_Checking.cpp"

    typedef struct {
        char* name;
        int addr;
    } label_t;

    const size_t start_capacity = 20;
#endif

