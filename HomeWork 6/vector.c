#include <stdlib.h>
#include <stdio.h>

int cauta(int* vector, int nr, int st, int dr){
  
  if((dr - st) == 1)
   if(vector[st] == nr)
     return 1;
   else
     return 0;
  
  int fius = -1;
  int fiud = -1;
  int status1 = 0, status2 = 0;
  int m = (st + dr) / 2;

  fius = fork();
  
  if(fius == 0){
        int x;
        x = cauta(vector, nr, st, m);
        exit(x);
	}
  else{
        fiud = fork();

        if(fiud == 0){
            int x;
            x = cauta(vector, nr, m, dr);
            exit(x);
        }
    }
 
  waitpid(fius, &status1, 0);
  waitpid(fiud, &status2, 0);
  return WEXITSTATUS(status1) + WEXITSTATUS(status2);  
}

int main(int argc, char* argv[]){

 int i, gasit = 0;
 int array[argc], number = 0;
 if(argc <= 2)
  {
    fprintf(stderr,"Utilizare: %s nr_cautat nr1, nr2, ..., nrn\n",argv[0]);
    return 1;
  }
 
 sscanf(argv[1],"%d",&number);

 for(i = 2; i < argc; i++)
     sscanf(argv[i],"%d",&array[i - 2]);

 if(gasit = cauta(array,number,0,argc - 2))
    printf("Numarul %d a fost gasit de %d ori.\n", number, gasit);
 else
    printf("Numarul %d nu a fost gasit.\n", number);

 return 0;
}

