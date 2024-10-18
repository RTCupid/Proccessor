//#include "TXLib.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Proccessor.h"

void Run ();

void MakeProgrammCode ();

void PrDump ();

static int* REG = NULL;
static stack_t STK = {};
static proc_t PRC = {};

int main ()
{
    printf ("# My proccessor\n");
    printf ("# (c) RTCupid, 2024\n\n");
    printf ("Start run()\n");

    REG = (int*)calloc (nregisters, sizeof (int));
    if (REG == NULL)
        {
        printf ("ERROR: calloc to Reg return NULL");
        return 0;
        }
    REG[DX] = 52;
    StackCtor (&STK, 8);

    Run ();


    printf ("# End of programm\n\n");

    return 0;
}

void Run ()
{
    PRC.code = (int*)calloc (start_capacity, sizeof (int));

    PRC.size = 0;
    MakeProgrammCode ();
    printf ("size_code = %d\n", PRC.size);

    int next = 1;

    PrDump ();
    while (next)
    {
        switch (PRC.code[PRC.ip])
        {
            case  CMD_PUSH: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d ", PRC.code[PRC.ip]);
                int arg = PRC.code[PRC.ip + 1];
                printf ("arg = %d\n", arg);
                StackPush (&STK, arg);

                PRC.ip += 2;
                break;
            };
            case CMD_PUSH_REG: {                                     //from Reg to stack
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d ", PRC.code[PRC.ip]);
                printf ("Reg[DX] = %d\n", REG[DX]);
                StackPush (&STK, REG[DX]);

                PRC.ip += 1;
                break;
            };
            case CMD_ADD: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);
                int a = 0;
                StackPop (&STK, &a);
                printf ("function ADD:\n");
                PrDump ();
                int b = 0;
                StackPop (&STK, &b);
                PrDump ();
                StackPush (&STK, a + b);
                PrDump ();

                PRC.ip += 1;
                break;
            };
            case CMD_SUB: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);
                int a = 0;
                StackPop (&STK, &a);
                int b = 0;
                StackPop (&STK, &b);

                StackPush (&STK, b - a);

                PRC.ip += 1;
                break;
            }
            case CMD_DIV: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);
                int a = 0;
                StackPop (&STK, &a);
                int b = 0;
                StackPop (&STK, &b);
                StackPush (&STK, b / a);

                PRC.ip += 1;
                break;
            }
            case CMD_MUL: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);
                int a = 0;
                StackPop (&STK, &a);
                int b = 0;
                StackPop (&STK, &b);
                StackPush (&STK, b * a);

                PRC.ip += 1;
                break;
            }
            case CMD_OUT: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);
                int a = 0;
                StackPop (&STK, &a);

                printf ("return value = <%d>\n", a);

                PRC.ip += 1;
                break;
            }
            case CMD_POP_REG: {                                      // from stack to Reg DX
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d ", PRC.code[PRC.ip]);

                int a = 0;
                StackPop (&STK, &a);
                REG[DX] = a;

                printf ("Reg[DX] = %d\n", REG[DX]);

                PRC.ip += 1;
                break;
            }
            case CMD_JMP: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);

                int arg = PRC.code[PRC.ip + 1];
                PRC.ip = arg;
                break;
            }
            case CMD_JA: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);

                int a = 0;
                int b = 0;
                StackPop (&STK, &b);
                StackPop (&STK, &a);

                if (b > a) {
                    int arg = PRC.code[PRC.ip + 1];
                    PRC.ip = arg;
                }
                else
                    PRC.ip += 2;
                break;

            }
            case CMD_HLT: {
                printf ("ip = %d ", PRC.ip);
                printf ("cmd = %d\n", PRC.code[PRC.ip]);
                next = 0;
                break;
            }
            default: {
                printf ("SINTXERROR: ip = <%d>, cmd = %d \n", PRC.ip, PRC.code[PRC.ip]);
                next = 0;
            }
        }
        PrDump ();
    }
    free (PRC.code);
}

void MakeProgrammCode ()
{
    FILE* file_code = fopen ("Programm_code.txt", "r");

    int cmd = 0;
    fscanf (file_code, "%d", &cmd);
    while (1)
    {
        PRC.code[PRC.ip] = cmd;
        PRC.ip++;
        if (cmd == -1)
            break;
        fscanf (file_code, "%d", &cmd);
    }
    PRC.size = PRC.ip;
    PRC.ip = 0;
    fclose (file_code);
}

void PrDump ()
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
    printf ("Registers: AX = %d | BX = %d | CX = %d | DX = %d\n", REG[AX], REG[BX], REG[CX], REG[DX]);



    printf ("--------------------------------------------------------------------------------\n\n\n");

}

