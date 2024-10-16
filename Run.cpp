#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Assembler.h"
#include "Proccessor.h"

void Run ();

void MakeProgrammCode (int* pr_code);

void PrDump ();

static int* REG = NULL;
static stack_t STK = {};

int main ()
{
    printf ("# My proccessor\n");
    printf ("# (c) RTCupid, 2024\n\n");
    printf ("Start run()\n");

    REG = (int*)calloc (4, sizeof (int));
    if (REG == NULL)
        {
        printf ("ERROR: calloc to Reg return NULL");
        return 0;
        }

    StackCtor (&STK, 5);

    Run ();

    printf ("# End of programm\n\n");

    return 0;
}

void Run ()
{
    int* pr_code = (int*)calloc (start_capacity, sizeof (int));

    MakeProgrammCode (pr_code);

    int ip = 0;
    int next = 1;
    while (next)
    {
        #pragma GCC diagnostic ignored "-Wunused-result"
        switch (pr_code[ip])
        {
            case  CMD_PUSH: {
                printf ("PC = %d ", ip);
                printf ("cmd = %d ", pr_code[ip]);
                int arg = pr_code[ip + 1];
                printf ("arg = %d\n", arg);
                StackPush (&STK, arg);

                ip += 2;
                break;
            };
            case CMD_PUSH_REG: {                                     //from Reg to stack
                printf ("ip = %d ", ip);
                printf ("cmd = %d ", pr_code[ip]);
                printf ("Reg[DX] = %d\n", REG[DX]);
                StackPush (&STK, REG[DX]);

                ip += 1;
                break;
            };
            case CMD_ADD: {
                printf ("ip = %d ", ip);
                printf ("cmd = %d\n", pr_code[ip]);
                int a = 0;
                StackPop (&STK, &a);
                int b = 0;
                StackPop (&STK, &b);
                StackPush (&STK, a + b);

                ip += 1;
                break;
            };
            case CMD_SUB: {
                printf ("ip = %d ", ip);
                printf ("cmd = %d\n", pr_code[ip]);
                int a = 0;
                StackPop (&STK, &a);
                int b = 0;
                StackPop (&STK, &b);

                StackPush (&STK, b - a);

                ip += 1;
                break;
            }
            case CMD_DIV: {
                printf ("ip = %d ", ip);
                printf ("cmd = %d\n", pr_code[ip]);
                int a = 0;
                StackPop (&STK, &a);
                int b = 0;
                StackPop (&STK, &b);
                StackPush (&STK, b / a);

                ip += 1;
                break;
            }
            case CMD_MUL: {
                printf ("ip = %d ", ip);
                printf ("cmd = %d\n", pr_code[ip]);
                int a = 0;
                StackPop (&STK, &a);
                int b = 0;
                StackPop (&STK, &b);
                StackPush (&STK, b * a);

                ip += 1;
                break;
            }
            case CMD_OUT: {
                printf ("ip = %d ", ip);
                printf ("cmd = %d\n", pr_code[ip]);
                int a = 0;
                StackPop (&STK, &a);

                printf ("return value = <%d>\n", a);

                ip += 1;
                break;
            }
            case CMD_POP_REG: {                                      // from stack to Reg DX
                printf ("ip = %d ", ip);
                printf ("cmd = %d ", pr_code[ip]);

                int a = 0;
                StackPop (&STK, &a);
                REG[DX] = a;

                printf ("Reg[DX] = %d\n", REG[DX]);

                ip += 1;
                break;
            }
            case CMD_JMP: {
                printf ("ip = %d ", ip);
                printf ("cmd = %d\n", pr_code[ip]);

                int arg = pr_code[ip + 1];
                ip = arg;
                break;
            }
            case CMD_HLT: {
                printf ("ip = %d ", ip);
                printf ("cmd = %d\n", pr_code[ip]);
                next = 0;
                break;
            }
            default: {
                printf ("SINTXERROR: ip = <%d>, cmd = %d \n", ip, pr_code[ip]);
                next = 0;
            }
        }
        #pragma GCC diagnostic warning "-Wunused-result"
    }
}

void MakeProgrammCode (int* pr_code)
{
    FILE* file_code = fopen ("Programm_code.txt", "r");

    int ip = 0;
    int i = 0;
    fscanf (file_code, "%d", &ip);
    while (1)
        {
        pr_code[i] = ip;
        i++;
        if (ip == -1)
            break;
        fscanf (file_code, "%d", &ip);
        }
    fclose (file_code);
}

void PrDump ()
{
printf ("ku");
}

