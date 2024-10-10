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
            case  Push:{
                printf ("PC = %d ", PC);
                int arg = 0;
                fscanf (file_code,"%d", &arg);
                printf ("%d\n", arg);
                StackPush (&stk, arg);
                break;
            }
            case Add:{
                printf ("PC = %d\n", PC);
                int a = 0;
                StackPop (&stk, &a);
                int b = 0;
                StackPop (&stk, &b);
                StackPush (&stk, a + b);
                break;
            }
            case Sub:{
                printf ("PC = %d\n", PC);int a = 0;
                StackPop (&stk, &a);
                int b = 0;
                StackPop (&stk, &b);

                StackPush (&stk, b - a);
                break;
            }
            case Out:{
                printf ("PC = %d\n", PC);
                int a = 0;
                StackPop (&stk, &a);
                int b = 0;
                StackPop (&stk, &b);
                StackPush (&stk, b/a);
                break;
            }
            case Div:{
                printf ("PC = %d\n", PC);
                int a = 0;
                StackPop (&stk, &a);

                printf ("return value = <%d>\n", a);
                break;
            }
            case Hlt:{
                printf ("PC = %d\n", PC);
                next = 0;
                break;
            }
            default:{
                printf ("SINTXERROR <%d>\n", PC);
            }
    }
}

