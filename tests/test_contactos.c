#include <stdio.h>
#include <stdlib.h>
#include "../Headers/contactos.h"

int main(void)
{
    if (action("add") != ADD)
    {
        fprintf(stderr, "action add failed\n");
        return 1;
    }
    if (action("ls") != LS)
    {
        fprintf(stderr, "action ls failed\n");
        return 1;
    }
    if (action("rm") != RM)
    {
        fprintf(stderr, "action rm failed\n");
        return 1;
    }
    if (action("sh") != SH)
    {
        fprintf(stderr, "action sh failed\n");
        return 1;
    }
    if (action("exit") != EXIT)
    {
        fprintf(stderr, "action exit failed\n");
        return 1;
    }
    printf("All tests passed\n");
    return 0;
}
