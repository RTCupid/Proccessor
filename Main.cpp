
#include "Compilator.cpp"
#include "Run.cpp"

int main ()
    {
    printf ("# My proccessor\n");
    printf ("# (c) RTCupid, 2024\n\n");
    int* pr_code = (int*)calloc (start_capacity, sizeof (int));
    Compilator (pr_code);
    printf ("Start run()\n");
    Run(pr_code);
    printf ("# End of programm");
    return 0;
    }

