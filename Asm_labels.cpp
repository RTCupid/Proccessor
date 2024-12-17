#include <string.h>

#include "Assembler.h"
#include "Asm_labels.h"

//.............................................................................
#define DBG if(0)

int IsLabel (char* cmd)
{
    int islabel = 0;
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] == ':') {
            islabel = 1;
            DBG printf ("                                                  <%s> is label\n", cmd);
        }
    DBG printf ("islabel = %d\n", islabel);
    return islabel;
}

//.............................................................................

void DumpLabels (label_t* LABELS, size_t index_lab)
{
    printf ("\nDumpLabels:\n");
    printf ("----------------------------------------------------------------------\n");

    printf ("index_lab = <%lu>\n", index_lab);

    for (size_t i = 0; i < index_lab; i++)
    {
        printf ("LABELS[%lu].name = <%s>\n", i, LABELS[i].name);
        printf ("LABELS[%lu].addr = <%d>\n", i, LABELS[i].addr);
    }



    printf ("----------------------------------------------------------------------\n\n");
}

//.............................................................................

void DumpFixup (fixup_t* FIXUP, size_t index_fix)
{
    printf ("\n DumpFixup: \n");
    printf ("----------------------------------------------------------------------\n");
    for (size_t i = 0; i < index_fix; i++)
    {
        printf ("FIXUP[%lu].name = <%s>\n", i, FIXUP[i].name);
        printf ("FIXUP[%lu].addr = <%d>\n", i, FIXUP[i].addr);
    }



    printf ("----------------------------------------------------------------------\n\n");
}

//.............................................................................

bool FindInLabels (size_t* nelem, char* name, size_t index_lab, label_t* LABELS)
{
    bool in_labels = false;
    while (*nelem < index_lab)                                                 //TD: while
    {
        DBG printf ("LABELS[%lu].name = <%s>\n", *nelem, LABELS[*nelem].name);
        DBG printf ("LABELS[%lu].addr = <%d>\n", *nelem, LABELS[*nelem].addr);

        if (strcmp (LABELS[*nelem].name, name) == 0)
        {
            in_labels = true;
            break;
        }
        *nelem = *nelem + 1;
    }
    return in_labels;
}

//.............................................................................

void AddLabel (bool in_labels, size_t nelem, char* cmd, int ip, label_t* LABELS, size_t* index_lab)
{
    if (in_labels)
    {
        if (LABELS[nelem].addr == -1)
        {
            LABELS[nelem].addr = ip;
        }
        else
        {
            printf ("ERROR: label already exsist\n");
        }
    }
    else if (!in_labels)
    {
        strcpy (LABELS[*index_lab].name, cmd);
        LABELS[*index_lab].addr = ip;
        (*index_lab)++;

        DBG printf ("\nLABEL ADDED:\n");
        DumpLabels (LABELS, *index_lab);
    }
}

//.............................................................................

void RunFixup (size_t index_fix, size_t index_lab, int* code, label_t* LABELS, fixup_t* FIXUP)
{
    for (size_t iFix = 0; iFix < index_fix; iFix++)
    {
        size_t nelem = 0;

        bool in_labels = FindInLabels (&nelem, FIXUP[iFix].name, index_lab, LABELS);

        if (in_labels)
            code[FIXUP[iFix].addr] = LABELS[nelem].addr;

        else                                                               //TD: == ELSE above
        {
            printf ("label not exsist\n");
            assert (0);
        }
    }
}
