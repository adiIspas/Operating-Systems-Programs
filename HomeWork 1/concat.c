#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *in;

    register int i, ch;

    FILE *out = fopen(argv[argc - 1],"w+");

    for(i = 1; i < argc - 1; i++)
    {
        if(NULL == (in = fopen(argv[i],"r")))
        {
            printf("Fisierul %s nu exista!", argv[i]);
            return 0;
        }

        while((ch = fgetc(in)) != EOF)
            fprintf(out,"%c", ch);
    }

    return 0;
}

