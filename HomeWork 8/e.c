#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
    char **argumente;
    int dimensiune = 2, i = 2, j, d;
 
    while(i < argc && argv[i][0] != '*'){      
     	  dimensiune++;
          i++;
         }

    argumente = (char**)malloc(dimensiune*sizeof(char*));
    if(argumente == NULL){
        fprintf(stderr,"Nu e memorie!");
        return 1;
	}

    argumente[0] = (char*)malloc(strlen(argv[1]) + 1);
    if(argumente[0] == NULL)
       {
        fprintf(stderr,"Nu e memorie!");
        free(argumente);
        return 1;
	}
    strcpy(argumente[0],argv[1]);
     
    i = 2; j = 1;

    while(i < argc && argv[i][0] != '*'){

          argumente[j] = (char*)malloc(strlen(argv[i])*sizeof(char) + 1);
          if(argumente[j] == NULL)
          {
             fprintf(stderr,"Nu e memorie!");
             j--;
             while(j){
                 free(argumente[j]);
                 j--;
		}
             free(argumente);
             return 1;
	    }
          strcpy(argumente[j],argv[i]);

          //if(i < argc - 1 && argv[i + 1][0] != '*')
             // strcat(argumente[j]," ");
      
          i++;
	  j++;
	}
 
    for(; i < argc - 1; i += 2){
        switch(argv[i][1]){
	  case '0' : {
                    d = open(argv[i + 1],O_RDONLY);
                    if(d == -1){
			perror(argv[i+1]);
                        j--;
                        while(j){
                 	free(argumente[j]);
                 	j--;
			}
             		free(argumente);
                        return 1;
                     }
		    dup2(d,STDIN_FILENO);
                    close(d);
 		   }
		    break;
          case '1' : {
		    d = open(argv[i + 1],O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
                    if(d == -1){
			perror(argv[i+1]);
                        j--;
                        while(j){
                 	free(argumente[j]);
                 	j--;
			}
             		free(argumente);
                        return 1;
                     }
		    dup2(d,STDOUT_FILENO);
                    close(d);
                   } 
                    break;
          case '2' : {
                    d = open(argv[i + 1],O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
                    if(d == -1){
			perror(argv[i+1]);
                        j--;
                        while(j){
                 	free(argumente[j]);
                 	j--;
			}
             		free(argumente);
                        return 1;
                     }
		    dup2(d,STDERR_FILENO);
                    close(d);
 		   }
		    break;
	}
    }
    argumente[j] = NULL;
    
    execv(argumente[0], argumente);
    execvp(argumente[0], argumente);
   
                      j--;
                        while(j){
                 	free(argumente[j]);
                 	j--;
			}
             		free(argumente);
                        return 1;
                  
    return 1;
}
