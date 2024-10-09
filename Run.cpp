#include <stdio.h>
#include <Stdbool.h>
#include <string.h>
#include "Assembler.h"

void Run ()
    {
    stack_t stk = {};
    StackCtor (&stk, 5);
    int next = 1;
    FILE* file = fopen ("Programm_asm.txt", "r");
    while (next)
        {
        char cmd[20] = "";
        //printf ("Enter command: ");
        fscanf (file,"%s", cmd);
        if (strcmp (cmd, "Push") == 0)
            {
            int arg = 0;
            //printf ("Enter push element: ");
            fscanf (file,"%d", &arg);
            StackPush (&stk, arg);
            }
        else if (strcmp (cmd, "Add") == 0)
            {
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);

            StackPush (&stk, a + b);
            }
        else if (strcmp (cmd, "Sub") == 0)
            {
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);

            StackPush (&stk, b - a);
            }
        else if (strcmp (cmd, "Out") == 0)
            {
            int a = 0;
            StackPop (&stk, &a);

            printf ("return value = <%d>\n", a);
            }
        else if (strcmp (cmd, "Div") == 0)
            {
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);
            StackPush (&stk, b/a);
            }
        else if (strcmp (cmd, "Hlt") == 0)
            {
            next = 0;
            break;
            }
        else
            printf ("SINTXERROR <%s>\n", cmd);
        }
    }

