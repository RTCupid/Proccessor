#include <stdio.h>
#include <Stdbool.h>
#include <string.h>
#include "Assembler.h"
#include "Proccessor.h"

void Compilator (int* pr_code);

int main ()
{
    printf ("# My proccessor\n");
    printf ("# (c) RTCupid, 2024\n\n");

    int* pr_code = (int*)calloc (start_capacity, sizeof (int));
    Compilator (pr_code);
    free (pr_code);

    printf ("# End of programm\n\n");
    return 0;
}

void Compilator (int* pr_code)
{
    int next = 1;
    FILE* file_asm  = fopen ("Programm_asm.txt", "r");
    FILE* file_code = fopen ("Programm_code.txt", "w");

    while (next)
    {
        char cmd[20] = "";
        fscanf (file_asm,"%s", cmd);
        printf ("cmd = <%s> ", cmd);
        if (stricmp (cmd, "Push") == 0)
        {
            fprintf (file_code, "17 ");
            printf ("17 ");

            int a = 0;
            fscanf (file_asm, "%d", &a);

            fprintf (file_code, "%d\n", a);
            printf ("a = %d\n", a);
        }
        else if (stricmp (cmd, "Push_Reg") == 0)
        {
            fprintf (file_code, "33 ");
            printf ("33\n");

            int a = 0;
            fscanf (file_asm, "%d", &a);
        }
        else if (stricmp (cmd, "Add") == 0)
        {
            fprintf (file_code, "2\n");
            printf ("2 \n");
        }
        else if (stricmp (cmd, "Sub") == 0)
        {
            fprintf (file_code, "3\n");
            printf ("3 \n");
        }
        else if (stricmp (cmd, "Div") == 0)
        {
            fprintf (file_code, "4\n");
            printf ("4 \n");
        }
        else if (stricmp (cmd, "Mul") == 0)
        {
            fprintf (file_code, "5\n");
            printf ("5 \n");
        }
        else if (stricmp (cmd, "Out") == 0)
        {
            fprintf (file_code, "6\n");
            printf ("6 \n");
        }
        else if (stricmp (cmd, "Pop") == 0)
        {
            fprintf (file_code, "7\n");
            printf ("7 \n");
        }
        if (stricmp (cmd, "Jmp") == 0)
        {
            fprintf (file_code, "8 ");
            printf ("8 ");

            int a = 0;
            fscanf (file_asm, "%d", &a);

            fprintf (file_code, "%d\n", a);
            printf ("a = %d\n", a);
        }
        else if (stricmp (cmd, "Hlt") == 0)
        {
            fprintf (file_code, "-1\n");
            printf ("-1 \n");
            next = 0;
            break;
        }
    }
    fclose (file_asm);
    fclose (file_code);
}
