#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Assembler.h"

void Compilator ();
void MakeCodeFile ();

static int* code;
//static label_t labels[];

int main ()
{
    printf ("# My processor\n");
    printf ("# (c) RTCupid, 2024\n\n");

    Compilator ();

    printf ("# End of programm\n\n");
    return 0;
}

void Compilator ()
{
    int next = 1;
    int ip = 0;
    FILE* file_asm  = fopen ("Programm_asm.txt", "r");

    code = (int*)calloc (start_capacity, sizeof (int));

    while (next) {
        char cmd[20] = "";
        fscanf (file_asm,"%s", cmd);
        printf ("cmd = <%s>\n", cmd);

        if (strcmp (cmd, "Push") == 0)
        {
            code[ip] = 17;

            int a = 0;
            fscanf (file_asm, "%d", &a);

            code [ip+1] = a;
            ip += 2;
        }
        else if (strcmp (cmd, "Push_Reg") == 0)
        {
            code[ip] = 33;

            int a = 0;
            fscanf (file_asm, "%d", &a);
            ip += 1;
        }
        else if (strcmp (cmd, "Add") == 0)
        {
            code[ip] = 2;
            ip += 1;
        }
        else if (strcmp (cmd, "Sub") == 0)
        {
            code[ip] = 3;
            ip += 1;
        }
        else if (strcmp (cmd, "Div") == 0)
        {
            code[ip] = 4;
            ip += 1;
        }
        else if (strcmp (cmd, "Mul") == 0)
        {
            code[ip] = 5;
            ip += 1;
        }
        else if (strcmp (cmd, "Out") == 0)
        {
            code[ip] = 6;
            ip += 1;
        }
        else if (strcmp (cmd, "Pop") == 0)
        {
            code[ip] = 7;
            ip += 1;
        }
        else if (strcmp (cmd, "Jmp") == 0)
        {
            code[ip] = 8;

            int a = 0;
            fscanf (file_asm, "%d", &a);

            code[ip + 1] = a;
            ip += 2;
        }
        else if (strcmp (cmd, "Hlt") == 0)
        {
            code[ip] = -1;
            ip += 1;
            next = 0;
            break;
        }
    }

    MakeCodeFile ();

    fclose (file_asm);
}

void MakeCodeFile ()
{
    FILE* file_code = fopen ("Programm_code.txt", "w");

    int ip = 0;
    while (1) {
        fprintf (file_code, "%d\n", code[ip]);
        printf ("%d\n", code[ip]);
        if (code[ip] == -1)
            break;


        ip++;
    }
    fclose (file_code);
}
