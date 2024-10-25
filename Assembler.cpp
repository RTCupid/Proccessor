#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Assembler.h"
#include "Enum.h"

//TODO: many .cpp and .h in future
// Don't forget about architecture of project

int main (/*int argc, char** argv*/) //TODO: K & R - аргументы командной строки и typedef
{
    printf ("# My processor\n");
    printf ("# (c) RTCupid, 2024\n\n");

    //AsmCtor()

    Asm ();                                                                    //TD: Compilator -> Asm

    printf ("# End of programm\n\n");
    return 0;
}

// function for file_asm -> code -> file_code..................................

void Asm ()
{
    int next = 1;
    int ip = 0;

    FILE* file_asm  = fopen ("Programm_asm.txt", "rb");                        //TODO: use argumnets of cmd in future!

    int* code       = (int*)     calloc (capacity_code,   sizeof (code[0]));
    label_t* LABELS = (label_t*) calloc (capacity_labels, sizeof (LABELS[0]));
    fixup_t* FIXUP  = (fixup_t*) calloc (capacity_fixup,  sizeof (FIXUP[0]));

    size_t index_lab = 0;
    size_t index_fix = 0;

    while (next)
    {
        char cmd[size_command] = "";                                           //TD: remove magic number
        fscanf (file_asm, "%s", cmd);
        printf (">>> cmd = <%s>\n", cmd);

        int id = IdCommand (cmd);
        printf ("\n\n>>>>>> <%d>\n\n", id);

        //if (!IsLabel (cmd)) {
        //    printf ("                                                        <%s> is not label\n", cmd);
        //}

        switch (id)
        {
            case LABEL_ID:
            {
                printf ("    <%s> is label\n", cmd);

                size_t nelem = 0;

                DumpLabels (LABELS, index_lab);

                bool in_labels = FindInLabels (&nelem, cmd, index_lab, LABELS);
                printf ("FindInLabels (%s) returned %d\n", cmd, in_labels);

                AddLabel (in_labels, nelem, cmd, ip, LABELS, &index_lab);
                break;
            }
            case PUSH_ID:                                    //TD: choose one register CAPITAL or small
            {
                code[ip] = CMD_PUSH;
                ip++;
                printf ("code[%d] = <%d>\n", ip - 1, code[ip - 1]);
                CompileArg (file_asm, code, &ip);
                break;
            }
            case POP_ID: //TODO: remove strings from code and make some array of structures with info about every command
            {
                code[ip] = CMD_POP; ip++;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                CompileArg (file_asm, code, &ip);
                break;
            }
            case ADD_ID:                                        //TD: make function that compares strings and returns number - command id
            {                                                   //TD: switch case
                code[ip] = CMD_ADD;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                ip += 1;
                break;
            }
            case SUB_ID:
            {
                code[ip] = CMD_SUB;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                ip += 1;
                break;
            }
            case DIV_ID:
            {
                code[ip] = CMD_DIV;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                ip += 1;
                break;
            }
            case MUL_ID:
            {
                code[ip] = CMD_MUL;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                ip += 1;
                break;
            }
            case OUT_ID:
            {
                code[ip] = CMD_OUT;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                ip += 1;
                break;
            }
            case JMP_ID:
            {
                code[ip] = CMD_JMP;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                DumpLabels (LABELS, index_lab);

                void* arg = calloc (max_len_cmd, sizeof (char));
                if (arg == NULL) {
                    printf ("calloc return NULL");
                    assert (0);
                }
                if (fscanf (file_asm, "%d", (int*)arg))
                {
                    code[ip + 1] = *((int*)arg);
                }
                else
                {
                    fscanf (file_asm, "%s", (char*)arg);

                    printf ("arg = <%s>\n", (char*)arg);

                    if (IsLabel ((char*)arg))
                    {
                        size_t nelem = 0;
                        bool in_labels = FindInLabels (&nelem, (char*)arg, index_lab, LABELS);
                        if (in_labels)
                        {
                            code[ip + 1] = LABELS[nelem].addr;
                        }
                        else
                        {
                            code[ip + 1] = -1;

                            FIXUP[index_fix].addr = ip + 1;
                            strcpy (FIXUP[index_fix].name, (char*)arg);

                            index_fix++;

                            strcpy (LABELS[index_lab].name, (char*)arg);
                            LABELS[index_lab].addr = -1;
                        }
                    }
                    else
                        printf ("arg Jmp is not label\n");
                }
                free (arg);
                ip += 2;
                break;
            }
            case JA_ID:
            {
                code[ip] = CMD_JA;
                printf ("code[%d] = <%d>\n", ip, code[ip]);

                DumpLabels (LABELS, index_lab);

                void* arg = calloc (max_len_cmd, sizeof (char));
                if (arg == NULL) {
                    printf ("calloc return NULL");
                    assert (0);
                }
                if (fscanf (file_asm, "%d", (int*)arg))
                    code[ip + 1] = *((int*)arg);
                else {
                    fscanf (file_asm, "%s", (char*)arg);

                    printf ("arg = <%s>\n", (char*)arg);

                    if (IsLabel ((char*)arg))
                    {
                        size_t nelem = 0;
                        bool in_labels = FindInLabels (&nelem, (char*)arg, index_lab, LABELS);

                        if (in_labels)
                        {
                        code[ip + 1] = LABELS[nelem].addr;
                        printf ("LABELS[%lu].addr = <%d>\n", nelem, LABELS[nelem].addr);
                        printf ("code[%d] = <%d>\n", ip + 1, code[ip + 1]);
                        }
                        else
                        {
                            code[ip + 1] = -1;

                            FIXUP[index_fix].addr = ip + 1;
                            strcpy (FIXUP[index_fix].name, (char*)arg);

                            index_fix++;

                            strcpy (LABELS[index_lab].name, (char*)arg);
                            LABELS[index_lab].addr = -1;
                        }
                    }
                    else
                        printf ("arg Ja is not label\n");
                }
                free (arg);
                ip += 2;
                break;
            }
            case HLT_ID:
            {
                code[ip] = CMD_HLT;
                printf ("code[%d] = <%d>\n\n", ip, code[ip]);

                ip += 1;
                next = 0;
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

    RunFixup (index_fix, index_lab, code, LABELS, FIXUP);

    MakeCodeFile (code);

    free (code);
    free (LABELS);
    free (FIXUP);
    fclose (file_asm);
}

//.............................................................................

void MakeCodeFile (int* code)
{
    FILE* file_code = fopen ("Programm_code.txt", "wb");

    int ip = 0;
    while (1) {
        fprintf (file_code, "%d\n", code[ip]);
        printf ("code[%d] = %d\n", ip, code[ip]);
        if (code[ip] == -1)
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
        argType = argType | 1;
        code[*ip] = argType; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
        code[*ip] = *((int*)arg); printf ("code[%d] = %d\n\n", *ip, code[*ip]); (*ip)++;
    }
    else if (fscanf (file_asm, "%s", arg)){
        printf("\n<%s>\n", arg);

        char* addrReg = strchr (arg, 'X'); if (addrReg != NULL) argType = argType | 2;
        printf ("addrReg = <%p>\n", addrReg);

        char* addrAdd = strchr (arg, '+'); if (addrAdd != NULL) argType = argType | 3;
        printf ("addrAdd = <%p>\n", addrAdd);

        char* addrRam = strchr (arg, '['); if (addrRam != NULL) argType = argType | 4;
        printf ("addrRam = <%p>\n", addrRam);

        if ((argType & 2) == 0)
            argType = argType | 1;

        printf ("argType = <%d>\n", argType);
        switch (argType)
        {
            case 1: //TODO: Make enum or smth but not MAGIC numbers
                code[*ip] = argType; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                break;
            case 2:
                code[*ip] = argType; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                code[*ip] = numReg; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                break;
            case 3:
                code[*ip] = argType; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                numNum = (int)atol (addrAdd + 1 * sizeof (char));
                code[*ip] = numNum; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                code[*ip] = numReg; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                break;
            case 5:
                code[*ip] = argType; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                numNum = (int)atol (addrRam + 1 * sizeof (char));
                code[*ip] = numNum; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                break;
            case 6:
                code[*ip] = argType; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                code[*ip] = numReg; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                break;
            case 7:
                code[*ip] = argType; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                numReg = *(addrReg - 1 * sizeof (char)) - 'A';
                numNum = (int)atol (addrAdd + 1 * sizeof (char));
                code[*ip] = numNum; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
                code[*ip] = numReg; printf ("code[%d] = %d\n", *ip, code[*ip]); (*ip)++;
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

//.............................................................................

int IsLabel (char* cmd)
{
    int islabel = 0;
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] == ':') {
            islabel = 1;
            printf ("                                                  <%s> is label\n", cmd);
        }
    printf ("islabel = %d\n", islabel);
    return islabel;
}

//.............................................................................

void DumpLabels (label_t* LABELS, size_t index_lab)
{
    printf ("\nDumpLabels:\n");
    printf ("----------------------------------------------------------------------\n");

    printf ("index_lab = <%lu>\n", index_lab);

    for (size_t i = 0; i < index_lab; i++) {
        printf ("LABELS[%lu].name = <%s>\n", i, LABELS[i].name);
        printf ("LABELS[%lu].addr = <%d>\n", i, LABELS[i].addr);
    }



    printf ("----------------------------------------------------------------------\n\n");
}

//.............................................................................

void DumpFixup (fixup_t* FIXUP, size_t index_fix)
{
    printf ("\n DumpFixup: \n");
    printf ("----------------------------------------------------------------------\n");
    for (size_t i = 0; i < index_fix; i++) {
        printf ("FIXUP[%lu].name = <%s>\n", i, FIXUP[i].name);
        printf ("FIXUP[%lu].addr = <%d>\n", i, FIXUP[i].addr);
    }



    printf ("----------------------------------------------------------------------\n\n");
}

//.............................................................................

bool FindInLabels (size_t* nelem, char* name, size_t index_lab, label_t* LABELS)
{
    bool in_labels = false;
    for (; *nelem < index_lab; *nelem = *nelem + 1)//TODO: while
    {
        printf ("LABELS[%lu].name = <%s>\n", *nelem, LABELS[*nelem].name);
        printf ("LABELS[%lu].addr = <%d>\n", *nelem, LABELS[*nelem].addr);

        if (strcmp (LABELS[*nelem].name, name) == 0)
        {
            in_labels = true;
            break;
        }
    }
    return in_labels;
}

//.............................................................................

void AddLabel (bool in_labels, size_t nelem, char* cmd, int ip, label_t* LABELS, size_t* index_lab)
{
    if (in_labels)
    {
        if (LABELS[nelem].addr == -1)
        {
            LABELS[nelem].addr = ip;
        }
        else
        {
            printf ("ERROR: label already exsist\n");
        }
    }
    else if (!in_labels)
    {
        strcpy (LABELS[*index_lab].name, cmd);
        LABELS[*index_lab].addr = ip;
        (*index_lab)++;

        printf ("\nLABEL ADDED:\n");
        DumpLabels (LABELS, *index_lab);
    }
}

//.............................................................................

void RunFixup (size_t index_fix, size_t index_lab, int* code, label_t* LABELS, fixup_t* FIXUP)
{
    for (size_t iFix = 0; iFix < index_fix; iFix++)
    {
        size_t nelem = 0;

        bool in_labels = FindInLabels (&nelem, FIXUP[iFix].name, index_lab, LABELS);

        if (in_labels)
            code[FIXUP[iFix].addr] = LABELS[nelem].addr;

        else                                                               //TD: == ELSE above
        {
            printf ("label not exsist\n");
            assert (0);
        }
    }
}

//compare cmd with string and return id command................................

int IdCommand (char* cmd)
{
    if (IsLabel (cmd))
    {
        return LABEL_ID;
    }
    if (strcmp (cmd, "push") == 0)                                    //TD: choose one register CAPITAL or small
    {
        return PUSH_ID;
    }
    if (strcmp (cmd, "pop") == 0) //TODO: remove strings from code and make some array of structures with info about every command
    {
        return POP_ID;
    }
    if (strcmp (cmd, "add") == 0) //TODO: make function that compares strings and returns number - command id
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
    }
    return -1;
}
