#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /** lineCount - Retine numarul de linii;
	wordCount - Retine numarul de cuvinte;
	characterCount - Retine numarul de caractere;
	sp - Variabila semafor pentru momentele in care se gaseste un spatiu. Implicit se pleca cu ea setata pe 1 pentru a contoriza primul cuvant;
	caseL - Retine daca s-a primit in linia de comanda optiunea de afisare a numarului de linii;
	caseW - Retine daca s-a primit in linia de comanda optiunea de afisare a numarului de cuvinte;
	caseC - Retine daca s-a primit in linia de comanda optiunea de afisare a numarului de caractere;
	ch - Caracter folosit la parcurgerea textului;
	
    */

    int lineCount = 0, wordCount = 0, characterCount = 0;
    int sp = 1, caseL = 0, caseW = 0, caseC = 0;
    int ch, prev = 32;
    FILE *in;

    switch(argc)
    {	
	// Cazul in care nu se da niciun parametru in linia de comanda. In acest caz se citeste textul din stdin si se afiseaza numarul de linii, cuvinte si caractere
        case 1:
                {
                in = stdin;
                while((ch = fgetc(in)) != EOF)
                   {
                    ++characterCount;

                    if(ch == '\n')
                      ++lineCount;

                    if(isspace(ch))
                      sp = 1;
                    else if(sp && (int)ch < 127 && (int)ch > 32)
                       {
                        ++wordCount;
                        sp = 0;
                        }
                    }

                printf("%d %d %d\n", lineCount, wordCount, characterCount);

                } break;

	// Cazul in care se citeste un parametru. Aici problema se imparte in 2 subprobleme. Prima, daca se citesc doar o combinatie -[lwc], iar a doua daca se citeste numele fisierului
        case 2:
                {
		    // Cazul in care se va introduce textul de la tastatura
                    int i;
                    if(argv[1][0] == '-')
                        {
                         for(i = 1; i < strlen(argv[1]); i++)
                            {
                                switch(argv[1][i])
                                {
                                    case 'l': caseL = 1; break;
                                    case 'w': caseW = 1; break;
                                    case 'c': caseC = 1; break;

                                    default:
                                            {
                                                fprintf(stderr,"Utilizare: %s -[lwc]\n", argv[0]);
                                                return 1;
                                            }
                                }
                            }

                        in = stdin;
                        while((ch = fgetc(in)) != EOF)
                           {
                            ++characterCount;

                            if(ch == '\n')
                              ++lineCount;

                            if(isspace(ch))
                              sp = 1;
                            else if(sp)
                               {
                                ++wordCount;
                                sp = 0;
                                }
                            }

                        if(caseL)
                            printf("%d ", lineCount);

                        if(caseW)
                            printf("%d ", wordCount);

                        if(caseC)
                            printf("%d ", characterCount);

                        printf("\n");
                        }
                    else
			// Cazul in care se va citit textul din fisier
                        {
                            if(NULL == (in = fopen(argv[1], "r")))
				{
                                    fprintf(stderr,"Fisierul %s nu exista\n", argv[1]);
                                    return 1;
                                }
                            while((ch = fgetc(in)) != EOF)
                               {
                                ++characterCount;

                                if(ch == '\n')
                                  ++lineCount;
				
                                if(isspace(ch))
                                  sp = 1;
                                else if(sp && ch > 32 && ch < 127)
                                   {
                                    ++wordCount;
                                    sp = 0;
                                    }
			}				
                            printf("%d %d %d %s\n", lineCount, wordCount, characterCount, argv[1]);
			    fclose(in);
                        }
                } break;
	
	// Cazul in care se primesc 2 parametrii. In acest caz parametrii pot fii doar -[lwc], optiuniile, si fisierul din care se va face citirea
        case 3:
                {

                 int i;
                 if(argv[1][0] == '-')
                    {
                     for(i = 1; i < strlen(argv[1]); i++)
                        {
                         switch(argv[1][i])
                         {
                            case 'l': caseL = 1; break;
                            case 'w': caseW = 1; break;
                            case 'c': caseC = 1; break;

                            default:
                                    {
                                        fprintf(stderr,"Utilizare: %s -[lwc] fisier\n", argv[0]);
                                        return 1;
                                    }
                         }
                        }
                    }
                 else
                    {
                       fprintf(stderr,"Utilizare: %s -[lwc] fisier\n", argv[0]);
                       return 1;
                    }

                if(NULL == (in = fopen(argv[2], "r")))
		{
                   fprintf(stderr,"Fisierul %s nu exista\n", argv[2]);
                   return 1;
                }

                while((ch = fgetc(in)) != EOF)
                   {
                    ++characterCount;

                    if(ch == '\n')
                      ++lineCount;

                    if(isspace(ch))
                      sp = 1;
                    else if(sp && (int)ch < 127 && (int)ch > 32)
                       {
                        ++wordCount;
                        sp = 0;
                        }
                    }

                if(caseL)
                    printf("%d ", lineCount);

                if(caseW)
                    printf("%d ", wordCount);

                if(caseC)
                    printf("%d ", characterCount);

                printf("%s \n", argv[2]);
		fclose(in);
                } break;

        default: {
		  fprintf(stderr,"Utilizare: %s -[lwc] fisier\n", argv[0]);
                  return 1; 
		} break;
    }

    return 0;
}
