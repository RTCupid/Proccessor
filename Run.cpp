//#include "TXLib.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Proccessor.h"
#include "Enum.h"

#include "Stack/Stack.cpp"
#include "Stack/Stack_Error_Checking.cpp"

#define DBG if(0)
                                                                               //TD: Cpu_t, CpuCtor, CpuDtor Run -> SPU

int main ()
{
    printf ("# My proccessor\n");
    printf ("# (c) RTCupid, 2024\n\n");
    printf ("Start run()\n");

    stack_t STK = {};
    StackCtor (&STK, 8);

    proc_t PRC = {};
    PrcCtor (&PRC);

    SPU (&STK, &PRC);

    PrcDtor (&PRC);

    StackDtor (&STK);

    printf ("# End of programm\n\n");
    return 0;
}

// Run processor...............................................................

void SPU (stack_t* STK, proc_t* PRC)
{
    MakeProgrammCode (PRC);
    DBG printf ("size_code = %d\n", PRC->size);

    int next = 1;

    //PrDump (*STK, *PRC);
    while (next)
    {
        //TODO: sqrt cos sin
        switch (PRC->code[PRC->ip]) //TODO: Codogen
        {
            case CMD_PUSH:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d ", PRC->code[PRC->ip]);

                int arg = GetArgPush (PRC, PRC->REG, PRC->RAM);

                DBG printf ("arg = %d\n", arg);
                StackPush (STK, arg);
                break;
            }
            case CMD_POP:
            {                                      // from stack to Reg DX
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d ", PRC->code[PRC->ip]);

                int value = 0;
                StackPop (STK, &value);

                int* addr = GetArgPop (PRC, PRC->REG, PRC->RAM);
                *addr = value;
                break;
            }
            case CMD_ADD:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int a = 0;
                StackPop (STK, &a);
                DBG printf (">>> a = <%d>\n", a);
                int b = 0;
                StackPop (STK, &b);
                DBG printf (">>> b = <%d>\n\n", b);

                StackPush (STK, a + b);
                DBG printf (">>> a + b = <%d>\n\n", a + b);

                PRC->ip += 1;
                break;
            }
            case CMD_SUB:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int a = 0;
                StackPop (STK, &a);
                int b = 0;
                StackPop (STK, &b);

                StackPush (STK, b - a);

                PRC->ip += 1;
                break;
            }
            case CMD_DIV:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int a = 0;
                StackPop (STK, &a);
                int b = 0;
                StackPop (STK, &b);

                StackPush (STK, b / a);

                PRC->ip += 1;
                break;
            }
            case CMD_MUL:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int a = 0;
                StackPop (STK, &a);
                int b = 0;
                StackPop (STK, &b);

                StackPush (STK, b * a);

                PRC->ip += 1;
                break;
            }
            case CMD_OUT:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int value = 0;
                StackPop (STK, &value);

                DBG printf ("return value = <%d>\n", value);

                PRC->ip += 1;
                break;
            }
            case CMD_JMP:
            {
                DBG printf ("ip = %d ", PRC->ip);
/*100*/         DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);
//14.80*1.20 -> 1480 * 120 ->
//1 -> 100 ->

                int arg = PRC->code[PRC->ip + 1];
                PRC->ip = arg;
                break;
            }
            case CMD_JA:
            {
                DBG printf ("Pause...\n");
                DBG printf ("Enter to continue\n");
                //getchar ();
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int a = 0;
                int b = 0;
                StackPop (STK, &b);
                StackPop (STK, &a);
                DBG printf ("b = %d\na = %d\n", b, a);

                if (b > a) {
                    int arg = PRC->code[PRC->ip + 1];
                    PRC->ip = arg;
                }
                else
                    PRC->ip += 2;
                DBG printf ("Pause...\n");
                DBG printf ("Enter to continue\n");
                //getchar ();
                break;

            }
            case CMD_SQRT:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int arg = 0;
                StackPop (STK, &arg);

                stack_elem_t returnedArg = sqrt (arg);
                StackPush (STK, returnedArg);
                PRC->ip += 1;
                break;
            }
            case CMD_CALL:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);
                PRC->ip++;

                int arg = PRC->code[PRC->ip];
                PRC->ip++;

                StackPush (&PRC->AddrRet, (PRC->ip));

                PRC->ip = arg;
                break;
            }
            case CMD_RET:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                int addr = 0;
                StackPop (&PRC->AddrRet, &addr);

                PRC->ip = addr;
                break;
            }
            case CMD_DRAW:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                DumpRAM (PRC->RAM);
                DBG printf ("Pause...\n");
                DBG printf ("Enter to continue\n");
                //getchar ();
                PRC->ip += 1;
                break;
            }
            case CMD_IN:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                printf ("Enter number: ");
                stack_elem_t arg = 0;
                scanf ("%d", &arg);

                StackPush (STK, arg);

                PRC->ip += 1;
                //getchar();
                break;
            }
            case CMD_HLT:
            {
                DBG printf ("ip = %d ", PRC->ip);
                DBG printf ("cmd = %d\n", PRC->code[PRC->ip]);

                next = 0;
                break;
            }
            default:
            {
                printf ("SINTXERROR: ip = <%d>, cmd = %d \n", PRC->ip, PRC->code[PRC->ip]);
                next = 0;
            }
        }
        //PrDump (*STK, *PRC);

        //printf ("Pause...\n");
        //printf ("Enter to continue\n");
        //getchar ();
    }
}

// Constructor of PRC structure................................................

void PrcCtor (proc_t* PRC)
{
    printf ("\nCtor Processor:\n");

    printf ("PRC->AddrRet = %p\n", &PRC->AddrRet);
    err_t error = StackCtor (&PRC->AddrRet, 10);
    PrintErrorStack (error, "StackCtor");

    //assert (0);
    StackDump (&PRC->AddrRet);

    PRC->REG = (int*)calloc (nregisters, sizeof (int));
    if (PRC->REG == NULL)
        {
        printf ("ERROR: calloc to Reg return NULL");
        assert (0);
        }

    PRC->RAM = (int*)calloc (nRAM, sizeof (int));
    if (PRC->RAM == NULL)
        {
        printf ("ERROR: calloc to RAM return NULL");
        assert (0);
        }

    PRC->code = (int*)calloc (capacity_code, sizeof (int));
    PRC->size = 0;

}

// Destructor of PRC structure.................................................

void PrcDtor (proc_t* PRC)
{
    StackDtor (&PRC->AddrRet);

    free (PRC->REG);
    PRC->REG = NULL;

    free (PRC->RAM);
    PRC->RAM = NULL;

    free (PRC->code);
    PRC->code = NULL;
}

// Making array of code........................................................

void MakeProgrammCode (proc_t* PRC)
{
    FILE* file_code = fopen ("Programm_code.txt", "r");

    int cmd = 0;
    fscanf (file_code, "%d", &cmd);
    while (1)
    {
        PRC->code[PRC->ip] = cmd;
        PRC->ip++;
        if (cmd == CMD_EOF)
            break;
        fscanf (file_code, "%d", &cmd);
    }
    PRC->size = PRC->ip;
    PRC->ip = 0;
    fclose (file_code);
}

//Dump for processor...........................................................

void PrDump (stack_t STK, proc_t PRC)
{
    printf ("\nDump Processor:\n");
    printf ("--------------------------------------------------------------------------------\n\n");
    printf ("ip:  ");
    for (int i = 0; i < PRC.size; i++)
    {
        if (i < 10)
            printf ("0%d ", i);
        else
            printf ("%d ",  i);
    }
    printf ("\n");

    printf ("cmd: ");
    for (int i = 0; i < PRC.size; i++)
    {
        if (PRC.code[i] == -1)
            printf ("%d ",  PRC.code[i]);
        else if (PRC.code[i] < 10)
            printf ("0%d ", PRC.code[i]);
        else
            printf ("%d ",  PRC.code[i]);
    }
    printf ("\n");

    printf("     ");
    for (int i = 0; i < PRC.ip * 2 + PRC.ip; i++)
    {
        printf ("~");
    }
    if (PRC.ip < 10)
        printf ("^ ip = 0%d\n", PRC.ip);
    else
        printf ("^ ip = %d\n",  PRC.ip);

    printf ("Stack:     ");
    for (int i = 0; i < (int)STK.capacity; i++)
    {
        printf ("%d ", STK.buffer[i]);
    }
    printf ("\n");
    printf ("Viktoria\n");
    printf ("Registers: AX = %d | BX = %d | CX = %d | DX = %d | EX = %d\n", (PRC.REG)[AX], (PRC.REG)[BX], (PRC.REG)[CX], (PRC.REG)[DX], (PRC.REG)[EX]);

    printf ("--------------------------------------------------------------------------------\n\n\n");
}

//.............................................................................

void DumpRAM (int* RAM)                                                        //TD: [100] -> magic number
{
    printf ("Dump RAM!\n");
    //for (int i = 0; i < nRAM; i++)
    //    printf ("%d", RAM[
    for (int i = 1; i < sqrt (nRAM); i++)
    {
        printf ("i = %d:", i);
        assert (i < sqrt (nRAM));
        for (int j = 1; j < sqrt (nRAM); j++)
        {
            assert (j < sqrt (nRAM));
            if (RAM[i * (int)sqrt (nRAM) + j] == 0)
                printf (".  ");
            else
                printf ("#  ");
        }
        printf ("\n");
    }
    printf ("\n");
}

//function to getting argument and return in...................................

int GetArgPush (proc_t* PRC, int* REG, int* RAM)
{
    PRC->ip++;
    int argType = PRC->code[PRC->ip]; PRC->ip++;
    int argValue = 0;
                                                                               //TD: & ^ -> MASK_MEM MASK_LABEL

    if (argType & MASK_NUM)                                                    //TD: magic number
    {
        DBG printf ("arg is number\n");
        argValue = PRC->code[PRC->ip];
        PRC->ip++;
    }
    if (argType & MASK_REG)
    {
        DBG printf ("arg is register\n");
        int regNum = PRC->code[PRC->ip];
        argValue += REG[regNum];
        PRC->ip++;
    }
    if (argType & MASK_RAM)
    {
        DBG printf ("call RAM\n");
        argValue = RAM[argValue];
    }

    return argValue;
}

int* GetArgPop (proc_t* PRC, int* REG, int* RAM)
{
    PRC->ip++;
    int argType = PRC->code[PRC->ip]; PRC->ip++;
    int* argValue = NULL;
    int SumArg = 0;

    if (argType & MASK_NUM)                                                    //TD: too
    {
        argValue = &PRC->code[PRC->ip];

        PRC->ip++;
    }

    if (argType & MASK_REG)
    {
        int regNum = PRC->code[PRC->ip];
        if (argValue != NULL)
        {
            SumArg = *argValue;
            SumArg += REG[regNum];

            argValue = &SumArg;
        }
        else
        {
            argValue = &(REG[regNum]);
        }
        PRC->ip++;
    }
    if (argType & MASK_RAM)
    {
        argValue = &(RAM[*argValue]);
    }
    //printf (">>>> addr argValuePop = <%p>\n", argValue);
    return argValue;
}

/*
N_DIGIT = 2 -> 10^2
100
148
PUSH 13.2819
1328
1.48 * 1.00
PUSH 1 -> 1 100 -> 1 1.00 -> pop 1 + 2.48
                -> 1 100  -> pop 1*148/100
PUSH 14.8 -> 1 1480 -> 1 14.8 ->
(double)1480
(int)14//.8
ja

MYLABEL:

push
pop
out

ret



main:
    in
    in
    in
    pop rax
    pop rbx
    pop rcx
    ...
hlt
*/
/*
CALL MYLABEL -> 18, 4
*/
