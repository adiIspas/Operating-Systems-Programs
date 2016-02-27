#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *in1;
    FILE *in2;

    register int ch1, ch2;
    int diff = 0;
    
    if(argc != 3)
    {
	fprintf(stderr,"Utilizare %s fisier1 fisier2\n", argv[0]);
        return 1;
    }
    
    in1 = fopen(argv[1], "r");
    in2 = fopen(argv[2], "r");
    
    while( ((ch1 = fgetc(in1)) != EOF) && ((ch2 = fgetc(in2)) != EOF) )
	if(ch1 != ch2)
	{
	   diff = 1;
	   break;
	}
   
    if(diff == 1)
	printf("Fisierul %s este diferit de fisierul %s\n", argv[1], argv[2]);

    return 0;
}

