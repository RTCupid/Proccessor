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
    if (file_code == NULL)
    {
        printf ("error open file");
        assert (0);
    }
    while (next)
    {
        int PC = -1;
        fscanf (file_code, "%d", &PC);
        if (PC == 1)
        {
            printf ("PC = %d ", PC);
            int arg = 0;
            fscanf (file_code,"%d", &arg);
            printf ("%d\n", arg);
            StackPush (&stk, arg);
        }
        else if (PC == 2)
        {
            printf ("PC = %d\n", PC);
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);

            StackPush (&stk, a + b);
        }
        else if (PC == 3)
        {
            printf ("PC = %d\n", PC);int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);

            StackPush (&stk, b - a);
        }
        else if (PC == 4)
        {
            printf ("PC = %d\n", PC);
            int a = 0;
            StackPop (&stk, &a);
            int b = 0;
            StackPop (&stk, &b);
            StackPush (&stk, b/a);
        }
        else if (PC == 5)
        {
            printf ("PC = %d\n", PC);
            int a = 0;
            StackPop (&stk, &a);

            printf ("return value = <%d>\n", a);
        }
        else if (PC == -1)
        {
            printf ("PC = %d\n", PC);
            next = 0;
            break;
        }
        else
            printf ("SINTXERROR <%d>\n", PC);
    }
}

