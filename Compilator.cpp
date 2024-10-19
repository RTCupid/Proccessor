#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Assembler.h"

void Compilator ();
void MakeCodeFile ();
int IsLabel (char* cmd);
void DumpLabels ();
void DumpFixup ();

static int* code;
static label_t* LABELS;
static size_t index_lab = 0;
static fixup_t* FIXUP;
static size_t index_fix = 0;

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

    code = (int*)calloc (capacity_code, sizeof (int));
    LABELS = (label_t*)calloc (capacity_labels, sizeof (int));
    FIXUP = (fixup_t*)calloc (capacity_fixup, sizeof (int));

    while (next) {
        char cmd[20] = "";
        fscanf (file_asm,"%s", cmd);
        printf ("cmd = <%s>\n", cmd);

        if (!IsLabel (cmd)) {
            printf ("                                                  <%s> is not label\n", cmd);
        }

        if (IsLabel (cmd)) {
            printf ("<%s> is label\n", cmd);
            bool in_labels = false;
            size_t i = 0;
            for (; i < index_lab; i++) {
                printf ("LABELS[%lu].name = <%s>\n", i, LABELS[i].name);
                printf ("LABELS[%lu].addr = <%d>\n", i, LABELS[i].addr);

                if (strcmp (LABELS[i].name, cmd) == 0) {
                    in_labels = true;
                }
            }
            if (in_labels) {
                if (LABELS[i].addr == -1) {
                    LABELS[i].addr = ip;
                }
                else
                    printf ("ERROR: label already exsist\n");
            }
            else {
                LABELS[index_lab].name = cmd;
                LABELS[index_lab].addr = ip;
                printf ("LABELS[%lu].name = <%s>\n", index_lab, LABELS[index_lab].name);
                printf ("LABELS[%lu].addr = <%d>\n", index_lab, LABELS[index_lab].addr);
                index_lab++;
            }
            ip += 1;
        }
        else if (strcmp (cmd, "Push") == 0)
        {
            code[ip] = 17;
            printf ("code[%d] = <%d>\n", ip, code[ip]);
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

            void* arg = calloc (max_len_cmd, sizeof (char));
            if (arg == NULL) {
                printf ("calloc return NULL");
                assert (0);
            }
            if (fscanf (file_asm, "%d", (int*)arg))
                code[ip + 1] = *((int*)arg);
            else {
                fscanf (file_asm, "%s", (char*)arg);

                printf ("arg = <%s>\n", (char*)arg);

                if (IsLabel ((char*)arg)) {
                    bool in_labels = false;

                    for (size_t i = 0; i < index_lab; i++) {
                        printf ("LABELS[%lu].name = <%s>\n", i, LABELS[i].name);
                        printf ("LABELS[%lu].addr = <%d>\n", i, LABELS[i].addr);

                        if (strcmp (LABELS[i].name, (char*)arg) == 0) {
                            code[ip + 1] = LABELS[i].addr;

                            in_labels = true;
                        }
                    }
                    if (!in_labels) {
                        code[ip + 1] = -1;

                        FIXUP[index_fix].addr = ip + 1;
                        FIXUP[index_fix].name = (char*)arg;

                        index_fix++;

                        LABELS[index_lab].name = (char*)arg;
                        LABELS[index_lab].addr = -1;
                    }
                }
                else
                    printf ("arg Jmp is not label\n");
            }
            free (arg);
            ip += 2;
        }
        else if (strcmp (cmd, "Ja") == 0)
        {
            code[ip] = 9;

            DumpLabels ();

            void* arg = calloc (max_len_cmd, sizeof (char));
            if (arg == NULL) {
                printf ("calloc return NULL");
                assert (0);
            }
            if (fscanf (file_asm, "%d", (int*)arg))
                code[ip + 1] = *((int*)arg);
            else {
                fscanf (file_asm, "%s", (char*)arg);

                printf ("arg = <%s>\n", (char*)arg);

                if (IsLabel ((char*)arg)) {
                    bool in_labels = false;

                    for (size_t i = 0; i < index_lab; i++) {
                        printf ("LABELS[%lu].name = <%s>\n", i, LABELS[i].name);
                        printf ("LABELS[%lu].addr = <%d>\n", i, LABELS[i].addr);

                        if (strcmp (LABELS[i].name, (char*)arg) == 0) {
                            code[ip + 1] = LABELS[i].addr;

                            in_labels = true;
                        }
                    }
                    if (!in_labels) {
                        code[ip + 1] = -1;

                        FIXUP[index_fix].addr = ip + 1;
                        FIXUP[index_fix].name = (char*)arg;

                        index_fix++;

                        LABELS[index_lab].name = (char*)arg;
                        LABELS[index_lab].addr = -1;
                    }
                }
                else
                    printf ("arg Ja is not label\n");
            }
            free (arg);
            ip += 2;
        }
        else if (strcmp (cmd, "Hlt") == 0)
        {
            code[ip] = -1;
            ip += 1;
            next = 0;
            break;
        }
        DumpLabels ();
    }

    printf ("Start FIXUP\n");

    for (size_t iFix = 0; iFix < index_fix; iFix++)
        for (size_t i = 0; i < index_lab; i++) {
            assert (i < index_lab);
            printf ("LABELS[%lu].name = <%s>\n", i, LABELS[i].name);
            printf ("LABELS[%lu].addr = <%d>\n", i, LABELS[i].addr);

            if (strcmp (LABELS[i].name, FIXUP[iFix].name) == 0) {
                code[FIXUP[iFix].addr] = LABELS[i].addr;
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
            printf ("                                                  <%s> is label\n", cmd);
        }
    printf ("islabel = %d\n", islabel);
    return islabel;
}

void DumpLabels ()
{
    printf ("\n DumpLabels: \n");
    printf ("----------------------------------------------------------------------\n");
    for (size_t i = 0; i < index_lab; i++) {
        printf ("LABELS[%lu].name = <%s>\n", i, LABELS[i].name);
        printf ("LABELS[%lu].addr = <%d>\n", i, LABELS[i].addr);
    }



    printf ("----------------------------------------------------------------------\n");
}

void DumpFixup ()
{
    printf ("\n DumpLabels: \n");
    printf ("----------------------------------------------------------------------\n");
    for (size_t i = 0; i < index_fix; i++) {
        printf ("FIXUP[%lu].name = <%s>\n", i, FIXUP[i].name);
        printf ("FIXUP[%lu].addr = <%d>\n", i, FIXUP[i].addr);
    }



    printf ("----------------------------------------------------------------------\n");
}
