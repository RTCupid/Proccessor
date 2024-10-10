#include "Compilator.cpp"
#include "Run.cpp"

int main ()
    {
    printf ("# My proccessor\n");
    printf ("# (c) RTCupid, 2024\n\n");

    int* pr_code = (int*)calloc (start_capacity, sizeof (int));

    code_t code = {
    pr_code,
    start_capacity,
    };
    Compilator (&code);

    for (int i = 1; i < 20; i++)
    {
        printf ("code.pr_code[%d] = %d", i, code.pr_code);
        if (code.pr_code[i] = -1)
        {
            break;
        }
    }

    printf ("Start run()\n");
    Run(&code);
    printf ("# End of programm");
    return 0;
    }
