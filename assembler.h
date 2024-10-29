//#include "Stack\Stack.h"
//#include "Stack\Config.h"
#ifndef ASSEMBLER
    #define ASSEMBLER

    #include "Stack/Stack.cpp"
    #include "Stack/Stack_Error_Checking.cpp"

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
    const size_t capacity_code = 200;
    const size_t capacity_labels = 10;
    const size_t capacity_fixup = 10;

    const size_t max_len_cmd = 20;

    typedef struct
    {
        char name[20];
        int addr;//-1 -> 10
    } label_t;

    typedef struct
    {
        int addr;
        char name[20];
    } fixup_t;

    typedef struct
    {
        int next;
        int ip;
        FILE* file_asm;
        int* code;
        label_t* LABELS;
        fixup_t* FIXUP;
        size_t index_lab;
        size_t index_fix;
        char cmd[size_command];
    } asm_t;

    void AsmCtor(asm_t* ASM);

    void AsmDtor (asm_t* ASM);

    void Assembler (asm_t* ASM);

    void MakeCodeFile (int* code);

    int IsLabel (char* cmd);

    void DumpLabels (label_t* LABELS, size_t index_lab);

    void DumpFixup (fixup_t* FIXUP, size_t index_fix);

    bool FindInLabels (size_t* nelem, char* name, size_t index_lab, label_t* LABELS);

    void AddLabel (bool in_labels, size_t nelem, char* cmd, int ip, label_t* LABELS, size_t* index_lab);

    void RunFixup (size_t index_fix, size_t index_lab, int* code, label_t* LABELS, fixup_t* FIXUP);

    void CompileArg (FILE* file_asm, int* code, int* ip);

    bool ChangeType (char* elem, int num, int* argType);

    int IdCommand (char* cmd);

    char* ToName (const char* name, char name_cmd[size_command]);
#endif

