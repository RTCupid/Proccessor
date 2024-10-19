//#include "Stack\Stack.h"
//#include "Stack\Config.h"
#ifndef ASSEMBLER
    #define ASSEMBLER

    #include "Stack/Stack.cpp"
    #include "Stack/Stack_Error_Checking.cpp"

    typedef struct {
        char name[20];
        int addr;
    } label_t;

    typedef struct {
        int addr;
        char name[20];
    } fixup_t;

    const size_t capacity_code = 20;
    const size_t capacity_labels = 10;
    const size_t capacity_fixup = 10;

    const size_t max_len_cmd = 20;
#endif

