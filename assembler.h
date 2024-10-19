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

    const size_t capacity_code = 20;
    const size_t capacity_labels = 10;

    const size_t max_len_cmd = 10;
#endif

