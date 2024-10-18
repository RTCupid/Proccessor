#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Assembler.h"

void Compilator ();
void MakeCodeFile ();
int IsLabel (char* cmd);

static int* code;
static label_t* labels;
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
    labels = (label_t*)calloc (start_capacity, sizeof (int));
    int index = 1;

    while (next) {
        char cmd[20] = "";
        fscanf (file_asm,"%s", cmd);
        printf ("cmd = <%s>\n", cmd);

        if (IsLabel (cmd)) {
            labels[index].name = cmd;
            labels[index].addr = ip;
            index++;
        }

        else if (strcmp (cmd, "Push") == 0)
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

            void* a = calloc (start_capacity, sizeof (char));
            if (a == NULL) {
                printf ("calloc return NULL");
                assert (0);
            }
            if (fscanf (file_asm, "%d", (int*)a))
                code[ip + 1] = *((int*)a);
            else {
                fscanf (file_asm, "%s", (char*)a);
                printf ("a = <%s>\n", (char*)a);
                for (size_t i = 0; i < start_capacity; i++)
                    if (strcmp (labels[i].name, (char*)a) == 0)
                        code[ip + 1] = labels[i].addr;
            }

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

int IsLabel (char* cmd)
{
    int islabel = 0;
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] == ':') {
            islabel = 1;
            printf ("<%s> is label\n", cmd);
        }
    return islabel;
}

void DumpLabels ()
    printf ("\n DumpLabels: \n");
    printf ("----------------------------------------------------------------------");




    printf ("----------------------------------------------------------------------");
