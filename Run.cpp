#include <stdio.h>
#include <Stdbool.h>
#include <string.h>
#include "Assembler.h"
#include "Proccessor.h"

void Run (int* pr_code)
{
    stack_t stk = {};
    StackCtor (&stk, 5);

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
