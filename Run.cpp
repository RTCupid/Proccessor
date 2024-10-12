#include <stdio.h>
#include <Stdbool.h>
#include <string.h>
#include "Assembler.h"
#include "Proccessor.h"

void Run ();

void MakeProgrammCode (int* pr_code);

static int* Reg = NULL;

int main ()
{
    printf ("# My proccessor\n");
    printf ("# (c) RTCupid, 2024\n\n");
    printf ("Start run()\n");

    Reg = (int*)calloc (4, sizeof (int));
    if (Reg == NULL)
        {
        printf ("ERROR: calloc return NULL");
        return 0;
        }

    Run ();

    printf ("# End of programm\n\n");
    return 0;
}

void Run ()
{
    stack_t stk = {};
    StackCtor (&stk, 5);

    int* pr_code = (int*)calloc (start_capacity, sizeof (int));

    MakeProgrammCode (pr_code);

    int PC = 0;
    int next = 1;
    while (next)
    {
        switch (pr_code[PC])
        {
            case  Push: {
                printf ("PC = %d ", PC);
                printf ("cmd = %d ", pr_code[PC]);
                int arg = pr_code[PC+1];
                printf ("arg = %d\n", arg);
                StackPush (&stk, arg);

                PC += 2;
                break;
            };
            case Add: {
                printf ("PC = %d ", PC);
                printf ("cmd = %d\n", pr_code[PC]);
                int a = 0;
                StackPop (&stk, &a);
                int b = 0;
                StackPop (&stk, &b);
                StackPush (&stk, a + b);

                PC += 1;
                break;
            };
            case Sub: {
                printf ("PC = %d ", PC);
                printf ("cmd = %d\n", pr_code[PC]);
                int a = 0;
                StackPop (&stk, &a);
                int b = 0;
                StackPop (&stk, &b);

                StackPush (&stk, b - a);

                PC += 1;
                break;
            }
            case Div: {
                printf ("PC = %d ", PC);
                printf ("cmd = %d\n", pr_code[PC]);
                int a = 0;
                StackPop (&stk, &a);
                int b = 0;
                StackPop (&stk, &b);
                StackPush (&stk, b / a);

                PC += 1;
                break;
            }
            case Mul: {
                printf ("PC = %d ", PC);
                printf ("cmd = %d\n", pr_code[PC]);
                int a = 0;
                StackPop (&stk, &a);
                int b = 0;
                StackPop (&stk, &b);
                StackPush (&stk, b * a);

                PC += 1;
                break;
            }
            case Out: {
                printf ("PC = %d ", PC);
                printf ("cmd = %d\n", pr_code[PC]);
                int a = 0;
                StackPop (&stk, &a);

                printf ("return value = <%d>\n", a);

                PC += 1;
                break;
            }
            case Hlt: {
                printf ("PC = %d ", PC);
                printf ("cmd = %d\n", pr_code[PC]);
                next = 0;
                break;
            }
            default: {
                printf ("SINTXERROR: PC = <%d>, cmd = %d\n", PC, pr_code[PC]);
                next = 0;
            }
        }
    }
}

void MakeProgrammCode (int* pr_code)
{
    FILE* file_code = fopen ("Programm_code.txt", "r");

    int PC = 0;
    int i = 0;
    fscanf (file_code, "%d", &PC);
    while (1)
        {
        pr_code[i] = PC;
        i++;
        if (PC == -1)
            break;
        fscanf (file_code, "%d", &PC);
        }
    fclose (file_code);
}
