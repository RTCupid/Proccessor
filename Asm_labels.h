typedef struct label_t
{
    char name[120];
    int addr;//-1 -> 10
} label_t;

typedef struct fixup_t
{
    int addr;
    char name[120];
} fixup_t;

int IsLabel (char* cmd);

void DumpLabels (label_t* LABELS, size_t index_lab);

void DumpFixup (fixup_t* FIXUP, size_t index_fix);

bool FindInLabels (size_t* nelem, char* name, size_t index_lab, label_t* LABELS);

void AddLabel (bool in_labels, size_t nelem, char* cmd, int ip, label_t* LABELS, size_t* index_lab);

void RunFixup (size_t index_fix, size_t index_lab, int* code, label_t* LABELS, fixup_t* FIXUP);


