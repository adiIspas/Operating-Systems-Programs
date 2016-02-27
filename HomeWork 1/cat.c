#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *in;
    register int i, ch;
    
    if(argc == 2)
    {
	in = fopen(argv[1],"r");
	
	while((ch = fgetc(in)) != EOF)
	    printf("%c",ch);
    }
    else
      if(argc == 1)
	{
	   in = stdin;
           while((ch = fgetc(in)) != EOF)
	       printf("%c",ch);
	}
      else
	{
	   fprintf(stderr,"Utilizare %s [fisier]", argv[0]);
           return 1;
	}

    return 0;
}

