#ifndef ASSEMBLER
    #define ASSEMBLER

    #include "Stack/Config.h"
    #include "Stack/Stack.h"

    //TODO: ARCHITECTURE OF PROGRAMM LIKE PREVIOUS PROJECTS asm_t { }

/*enum cmd_id_t
    {
        LABEL_ID = 0,
        PUSH_ID,
        POP_ID,
        ADD_ID,
        SUB_ID,
        DIV_ID,
        MUL_ID,
        OUT_ID,
        JMP_ID,
        JA_ID,
        COS_ID,
        SIN_ID,
        SQRT_ID,
        HLT_ID = -1,
    };*/
    enum arg_t
    {
        ARG_NUM = 1,
        ARG_REG = 2,
        ARG_REG_NUM = 3,
        ARG_RAM_NUM = 5,
        ARG_RAM_REG = 6,
        ARG_RAM_REG_NUM = 7,
    };

    const size_t size_command = 120;
    const size_t capacity_code = 500;
    const size_t capacity_labels = 100;
    const size_t capacity_fixup = 100;

    const size_t max_len_cmd = 120;

    struct label_t;
    struct fixup_t;

    typedef struct
    {
        int ip;
        FILE* file_asm;
        int* code;
        label_t* LABELS;
        fixup_t* FIXUP;
        stack_t* AddrFunc;
        size_t index_lab;
        size_t index_fix;
        size_t index_addr;
        char cmd[size_command];
    } asm_t;

    void AsmCtor (asm_t* ASM, char* asm_file);

    void AsmDtor (asm_t* ASM);

    void Assembler (asm_t* ASM);

    void SkipComment (asm_t* ASM);

    void MakeCodeFile (int* code);

    void CompileArg (FILE* file_asm, int* code, int* ip);

    bool ChangeType (char* elem, int num, int* argType);

    int IdCommand (char* cmd);

    char* ToName (const char* name, char name_cmd[size_command]);

    bool JmpFunc (asm_t* ASM);
#endif

