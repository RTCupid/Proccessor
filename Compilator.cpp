#include <stdio.h>
#include <Stdbool.h>
#include <string.h>
#include "Assembler.h"
#include "Proccessor.h"

void Compilator (code_t* code);

void MakeProgrammCode (code_t* code);

void Compilator (code_t* code)
{
    int next = 1;
    FILE* file_asm  = fopen ("Programm_asm.txt", "r");
    FILE* file_code = fopen ("Programm_code.txt", "w");

    while (next)
    {
        char cmd[20] = "";
        fscanf (file_asm,"%s", cmd);
        printf ("cmd = <%s> ", cmd);
        if (strcmp (cmd, "Push") == 0)
        {
            fprintf (file_code, "1 ");
            printf ("1 ");
            int a = 0;
            fscanf (file_asm, "%d", &a);
            fprintf (file_code, "%d\n", a);
            printf ("a = %d\n", a);
        }
        else if (strcmp (cmd, "Add") == 0)
        {
            fprintf (file_code, "2\n");
            printf ("2 \n");
        }
        else if (strcmp (cmd, "Sub") == 0)
        {
            fprintf (file_code, "3\n");
            printf ("3 \n");
        }
        else if (strcmp (cmd, "Div") == 0)
        {
            fprintf (file_code, "4\n");
            printf ("4 \n");
        }
        else if (strcmp (cmd, "Out") == 0)
        {
            fprintf (file_code, "5\n");
            printf ("5 \n");
        }
        else if (strcmp (cmd, "Hlt") == 0)
        {
            fprintf (file_code, "-1\n");
            printf ("-1 \n");
            next = 0;
            break;
        }
    }
    fclose (file_asm);
    fclose (file_code);

    MakeProgrammCode (code);
}

void MakeProgrammCode (code_t* code)
{
    FILE* file_code = fopen ("Programm_code.txt", "r");

    int PC = 0;
    int i = 0;
    fscanf (file_code, "%d", &PC);
    while (PC != -1)
    {
        if (code->size >= code->capacity-3)
        {
            printf ("size = <%d> capacity = <%d>\n", code->size, code->capacity);
            code->pr_code = (int*)realloc (code->pr_code, code->capacity * sizeof (int) * FACTOR);
            code->capacity *= FACTOR;
            printf ("size = <%d> capacity = <%d>\n", code->size, code->capacity);
            if (code->pr_code == NULL)
            {
                printf ("Realloc error");
                assert (0);
            }
        }
            code->pr_code[i] = PC;
            code->size++;
            i++;
            fscanf (file_code, "%d", &PC);
    }
    fclose (file_code);
}
