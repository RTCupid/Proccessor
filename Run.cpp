#include <stdio.h>
#include <Stdbool.h>
#include <string.h>
#include "Assembler.h"

void Run ()
    {
    stack_t stk = {};
    StackCtor (&stk, 5);
    int next = 1;
    FILE* file_code = fopen ("Programm_code.txt", "r");
    while (next)
        {
        int cmd = -1;
        fscanf (file_code,"%d", cmd);
        if (cmd == 1)
            {
            int arg = 0;
            fscanf (file_code,"%d", &arg);
            StackPush (&stk, arg);
            }
        else if (cmd == 2)
            {
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);

            StackPush (&stk, a + b);
            }
        else if (cmd == 3)
            {
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);

            StackPush (&stk, b - a);
            }
        else if (cmd == 4)
            {
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);
            StackPush (&stk, b/a);
            }
        else if (cmd == 5)
            {
            int a = 0;
            StackPop (&stk, &a);

            printf ("return value = <%d>\n", a);
            }
        else if (cmd == -1)
            {
            next = 0;
            break;
            }
        else
            printf ("SINTXERROR <%d>\n", cmd);
        }
    }

