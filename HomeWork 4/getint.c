#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int getint(int d){
    int numar = 0, negativ = 1;
    char ch;

    //pozitieInceput = lseek(d,0l,SEEK_CUR);

    /// sarim peste eventualele caractere albe(spatiu, tab, sfarsit de linie)
    if(read(d,&ch,sizeof(char))<=0)
        {
            errno = EIO;
            return 0;
        }

    while(ch == ' ' || ch == '\t' || ch == '\n')
         if(read(d,&ch,sizeof(char))<=0)
            {
                errno = EIO;
                return 0;
            }

    /// verificam semnul
    if(ch == '-')
        negativ = -1;
    else if(ch == '+');
    else
        /// verificam daca este un caracter ce nu poate face parte dintr-un numar
        if(ch < 48 || ch > 57)
        {
            /// trebuie setat errno

            /// mutam indicatorul din fisier inapoi
            //lseek(d,0l,pozitieInceput);
            lseek(d,-1,SEEK_CUR);
            errno = EIO;
            return 0;
        }
    else
        /// in caz contrar este in caracter ce face parte dintr-un numar
        numar = numar * 10 + ch -48;

    /// citim atata timp cat avem ceva in fisier si incercam sa construim numarul
    while(read(d,&ch,sizeof(char)) > 0){
        /// daca nu este caracter valid ne oprim
        if(ch < 48 || ch > 57)
            {
                /// mutam indicatorul din fisier inapoi
                //lseek(d,0l,pozitieInceput);
                lseek(d,-1,SEEK_CUR);
                return numar * negativ;
            }
        else
        /// daca este caracter valid il adaugam la numar
        //if(ch >=48 && ch <= 57)
            numar = numar*10 + ch - 48;
   }
  return numar*negativ;
}

int main(){

int in;
int x = 0, y = 0;
char input[] = "f";

in = open(input, O_RDONLY);

/// apel la getint();
x = getint(in);
y = getint(in);
printf("%d %d\n",x,y);
close(in);

/// apel la fscanf()
FILE *f;
in = open(input, O_RDONLY);
f=fdopen(in,"r");
fscanf(f,"%d",&y);
close(in);

/// afisarea rezultatelor intoarse de cele 2 functii
printf("Functia getint(): %d\n",x);
printf("Functia fscanf(): %d\n",y);

return 0;
}

