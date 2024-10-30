#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Assembler.h"
#include "Asm_labels.h"
#include "Enum.h"

#include "Stack/Stack.cpp"
#include "Stack/Stack_Error_Checking.cpp"

//TD: many .cpp and many .h in future
// Don't forget about architecture of project

int main (/*int argc, char** argv*/) //TODO: K & R - аргументы командной строки и typedef
{
    printf ("# My processor\n");
    printf ("# (c) RTCupid, 2024\n\n");

    asm_t ASM = {};
    AsmCtor(&ASM);

    Assembler (&ASM);

    AsmDtor (&ASM);                                                                    //TD: Compilator -> Asm

    printf ("# End of programm\n\n");
    return 0;
}

// function for file_asm -> code -> file_code..................................

void Assembler (asm_t* ASM)
{
    while (1)
    {                                          //TD: remove magic number
        int endCompile = fscanf (ASM->file_asm, "%s", ASM->cmd);
        printf (">>> cmd = <%s>\n", ASM->cmd);

        if (endCompile == EOF)
        {
            (ASM->code)[ASM->ip] = CMD_EOF;
            break;
        }
        int id = IdCommand (ASM->cmd);
        printf ("\n\n>>>>>> <%d>\n\n", id);

        //if (!IsLabel (cmd)) {
        //    printf ("                                                        <%s> is not label\n", cmd);
        //}

        switch (id)
        {
            case CMD_LABEL:
            {
                printf ("    <%s> is label\n", ASM->cmd);

                size_t nelem = 0;

                DumpLabels (ASM->LABELS, ASM->index_lab);

                bool in_labels = FindInLabels (&nelem, ASM->cmd, ASM->index_lab, ASM->LABELS);
                printf ("FindInLabels (%s) returned %d\n", ASM->cmd, in_labels);

                AddLabel (in_labels, nelem, ASM->cmd, ASM->ip, ASM->LABELS, &(ASM->index_lab));
                break;
            }
            case CMD_PUSH:                                    //TD: choose one register CAPITAL or small
            {
                (ASM->code)[ASM->ip] = CMD_PUSH;
                ASM->ip++;
                printf ("code[%d] = <%d>\n", ASM->ip - 1, (ASM->code)[ASM->ip - 1]);
                CompileArg (ASM->file_asm, ASM->code, &(ASM->ip));
                break;
            }
            case CMD_POP:
            {
                (ASM->code)[ASM->ip] = CMD_POP;
                ASM->ip++;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                CompileArg (ASM->file_asm, ASM->code, &(ASM->ip));
                break;
            }
            case CMD_ADD:                                        //TD: make function that compares strings and returns number - command id
            {                                                   //TD: switch case
                (ASM->code)[ASM->ip] = CMD_ADD;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            case CMD_SUB:
            {
                (ASM->code)[ASM->ip] = CMD_SUB;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            case CMD_DIV:
            {
                (ASM->code)[ASM->ip] = CMD_DIV;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            case CMD_MUL:
            {
                (ASM->code)[ASM->ip] = CMD_MUL;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            case CMD_OUT:
            {
                (ASM->code)[ASM->ip] = CMD_OUT;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            case CMD_JMP:
            {
                (ASM->code)[ASM->ip] = CMD_JMP;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                bool err_t = JmpFunc (ASM);

                if (err_t)
                {
                    printf ("arg jmp is not label");
                    assert(0);
                }
                break;
            }
            case CMD_JA:
            {
                (ASM->code)[ASM->ip] = CMD_JA;
                printf ("code[%d] = <%d>\n", ASM->ip, (ASM->code)[ASM->ip]);

                bool err_t = JmpFunc (ASM);

                if (err_t)
                {
                    printf ("arg ja is not label");
                    assert(0);
                }
                break;
            }
            case CMD_CALL:
            {
                (ASM->code)[ASM->ip] = CMD_CALL;
                printf ("code[%d] = <%d>\n", ASM->ip, (ASM->code)[ASM->ip]);

                bool err_t = JmpFunc (ASM);
                if (err_t)
                {
                    printf ("arg call is not label");
                    assert(0);
                }
                break;
            }
            case CMD_RET:
            {
                (ASM->code)[ASM->ip] = CMD_RET;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            case CMD_DRAW:
            {
                (ASM->code)[ASM->ip] = CMD_DRAW;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            case CMD_HLT:
            {
                (ASM->code)[ASM->ip] = CMD_HLT;
                printf ("code[%d] = <%d>\n\n", ASM->ip, (ASM->code)[ASM->ip]);

                ASM->ip += 1;
                break;
            }
            default:
            {
                printf ("unknown ID\n");
                assert(0);
            }
        }
        //DumpLabels (LABELS, index_lab);
    }

    printf ("Start FIXUP\n");

    DumpFixup (ASM->FIXUP, ASM->index_fix);

    RunFixup (ASM->index_fix, ASM->index_lab, ASM->code, ASM->LABELS, ASM->FIXUP);

    MakeCodeFile (ASM->code);
}

// Constructor of ASM structure................................................

void AsmCtor(asm_t* ASM)
{
    ASM->ip = 0;

    //ASM->AddrFunc = {};
    //StackCtor (ASM->AddrFunc, 20);

    ASM->file_asm  = fopen ("Programm_asm.txt", "rb");                        //TODO: use argumnets of cmd in future! ??????

    ASM->code       = (int*) calloc (capacity_code,   sizeof (ASM->code[0]));
    ASM->LABELS = (label_t*) calloc (capacity_labels, sizeof (ASM->LABELS[0]));
    ASM->FIXUP  = (fixup_t*) calloc (capacity_fixup,  sizeof (ASM->FIXUP[0]));

    ASM->index_lab = 0;
    ASM->index_fix = 0;
    ASM->index_addr = 0;
}

// Destructor of ASM structures................................................

void AsmDtor (asm_t* ASM)
{
    free (ASM->code);
    ASM->code = NULL;

    free (ASM->LABELS);
    ASM->LABELS = NULL;

    free (ASM->FIXUP);
    ASM->FIXUP = NULL;

    fclose (ASM->file_asm);
}

//.............................................................................

void MakeCodeFile (int* code)
{
    FILE* file_code = fopen ("Programm_code.txt", "wb");

    int ip = 0;
    while (1) {
        fprintf (file_code, "%d\n", code[ip]);
        printf ("code[%d] = %d\n", ip, code[ip]);
        if (code[ip] == CMD_EOF)
            break;


        ip++;
    }
    fclose (file_code);
}
//.............................................................................

void CompileArg (FILE* file_asm, int* code, int* ip)
{
    int argType = 0;
    char* arg = (char*)calloc (size_command, sizeof (char)); //TD: Magic number
    int numReg = 0;
    int numNum = 0;

    if (fscanf (file_asm, "%d", (int*)arg))
    {
        argType |=  1;
        code[*ip] = argType;
        printf ("code[%d] = %d\n", *ip, code[*ip]);
        (*ip)++;

        code[*ip] = *((int*)arg);
        printf ("code[%d] = %d\n\n", *ip, code[*ip]);
        (*ip)++;
    }
    else if (fscanf (file_asm, "%s", arg)){
        printf("\n<%s>\n", arg);

        char* addrReg = strchr (arg, 'X');
        if (addrReg != NULL)
            argType = argType | 2;
        printf ("addrReg = <%p>\n", addrReg);

        char* addrAdd = strchr (arg, '+');
        if (addrAdd != NULL)
            argType = argType | 3;
        printf ("addrAdd = <%p>\n", addrAdd);

        char* addrRam = strchr (arg, '[');
        if (addrRam != NULL)
            argType = argType | 4;
        printf ("addrRam = <%p>\n", addrRam);

        if ((argType & 2) == 0)
            argType = argType | 1;

        printf ("argType = <%d>\n", argType);
        switch (argType)
        {
            case ARG_NUM:                                                      //TD: Make enum or smth but not MAGIC numbers
                code[*ip] = argType;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;
                break;
            case ARG_REG:
                code[*ip] = argType;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;

                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                code[*ip] = numReg;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;
                break;
            case ARG_REG_NUM:
                code[*ip] = argType;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;

                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                numNum = (int)atol (addrAdd + 1 * sizeof (char));
                code[*ip] = numNum;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;

                code[*ip] = numReg;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;
                break;
            case ARG_RAM_NUM:
                code[*ip] = argType;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;

                numNum = (int)atol (addrRam + 1 * sizeof (char));
                code[*ip] = numNum;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;
                break;
            case ARG_RAM_REG:
                code[*ip] = argType;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;

                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                code[*ip] = numReg;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;
                break;
            case ARG_RAM_REG_NUM:
                code[*ip] = argType;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;

                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                numNum = (int)atol (addrAdd + 1 * sizeof (char));
                code[*ip] = numNum;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;

                code[*ip] = numReg;
                printf ("code[%d] = %d\n", *ip, code[*ip]);
                (*ip)++;
                break;
            default:
                printf ("ERROR: Compile arguments!\n");
                assert (0);
        }
        printf ("\n");
    }
    free (arg);
}

bool ChangeType (char* elem, int num, int* argType)
{
    if (elem != NULL)
    {
        *argType = *argType | num;
        return true;
    }
    else
        return false;
}


//compare cmd with string and return id command................................

int IdCommand (char* cmd)
{
    #define DEF_CMD_(name, id, ...)                         \
            if (strcmp (cmd, ToName (#name, name_cmd)) == 0)\
            {                                               \
                return CMD_##name;                          \
            }

    char name_cmd[size_command] = {};

    printf ("name_cmd = %p\n",    name_cmd);
    printf ("name_cmd[0] = <%c>\n", name_cmd[0]);

    if (IsLabel (cmd))
    {
        return CMD_LABEL;
    }
    #include "Commands.h"
    /*else*/
    printf ("unknown command\n");
    return -1;
    #undef DEF_CMD_
}

char* ToName (const char* name, char name_cmd[size_command])
{
    for (size_t i = 0; i < size_command; i++)                                  // clear array of name
    {
        assert (i < size_command);
        name_cmd[i] = '\0';
    }
    size_t index = 0;
    while (name[index] != '\0')
    {
        name_cmd[index] = (char)tolower ((name[index]));
        index++;
    }
    printf ("in ToName (...) name_cmd = <%s>\n", name_cmd);
    return name_cmd;
}

bool JmpFunc (asm_t* ASM)
{
    DumpLabels (ASM->LABELS, ASM->index_lab);

    ASM->ip++;

    char arg[max_len_cmd] = {};

    if (fscanf (ASM->file_asm, "%d", (int*)arg))
    {
        (ASM->code)[ASM->ip] = *((int*)arg);
        ASM->ip++;
    }
    else {
        fscanf (ASM->file_asm, "%s", (char*)arg);

        printf ("arg = <%s>\n", (char*)arg);

        if (IsLabel ((char*)arg))
        {
            size_t nelem = 0;
            bool in_labels = FindInLabels (&nelem, (char*)arg, ASM->index_lab, ASM->LABELS);

            if (in_labels)
            {
            (ASM->code)[ASM->ip] = (ASM->LABELS)[nelem].addr;
            ASM->ip++;
            //StackPush (ASM->AddrFunc, (ASM->LABELS)[nelem].addr);

            printf ("LABELS[%lu].addr = <%d>\n", nelem, (ASM->LABELS)[nelem].addr);
            printf ("code[%d] = <%d>\n", ASM->ip, (ASM->code)[ASM->ip]);
            }
            else
            {
                (ASM->code)[ASM->ip] = -1;
                //StackPush (ASM->AddrFunc, -1);

                (ASM->FIXUP)[(ASM->index_fix)].addr = ASM->ip;
                strcpy ((ASM->FIXUP)[ASM->index_fix].name, (char*)arg);

                ASM->index_fix++;

                strcpy ((ASM->LABELS)[ASM->index_lab].name, (char*)arg);
                (ASM->LABELS)[ASM->index_lab].addr = -1;
                ASM->ip++;
            }
        }
        else
            return 1;
    }
    return 0;
}

/*if (strcmp (cmd, "push") == 0)                                    //TD: choose one register CAPITAL or small
    {
        return PUSH_ID;
    }
    if (strcmp (cmd, "pop") == 0) //TODO: remove strings from code and make some array of structures with info about every command
    {
        return POP_ID;
    }
    if (strcmp (cmd, "add") == 0) //TD: make function that compares strings and returns number - command id
    {                             // switch case
        return ADD_ID;
    }
    if (strcmp (cmd, "sub") == 0)
    {
        return SUB_ID;
    }
    if (strcmp (cmd, "div") == 0)
    {
        return DIV_ID;
    }
    if (strcmp (cmd, "mul") == 0)
    {
        return MUL_ID;
    }
    if (strcmp (cmd, "out") == 0)
    {
        return OUT_ID;
    }
    if (strcmp (cmd, "jmp") == 0)
    {
        return JMP_ID;
    }
    if (strcmp (cmd, "ja") == 0)
    {
        return JA_ID;
    }
    if (strcmp (cmd, "hlt") == 0)
    {
        return HLT_ID;
    }*/
