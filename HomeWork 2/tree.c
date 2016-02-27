#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>

int directoare = 0, fisiere = 0, tab = 1;

int tree(const char *adresa)
{   
    int i;
    char cale[256], specificator[256];
    DIR *pD;
    struct dirent *pDe;
    struct stat dS;

    if((pD=opendir(adresa))==NULL)
	{
          perror(adresa);
	  return -1;
	}

    strcpy(cale,adresa);
    
    if(strlen(cale) > 0)
    {if(cale[strlen(cale) - 1] != '/')
          strcat(cale,"/");}
    else
    	{closedir(pD); return 0; }

    while((pDe=readdir(pD)) != NULL){
	  strcpy(specificator,cale);
      strcat(specificator,pDe->d_name);

	  if(strcmp(pDe->d_name,".") == 0 || strcmp(pDe->d_name,"..") == 0)
		continue;

	for(i = 0; i < tab; i++)
		printf("  ");
	printf("%s\n", pDe->d_name);

 	stat(specificator,&dS);
   	if(S_ISDIR(dS.st_mode))
		{
		 //char caleTemp[256];
		 //strcpy(caleTemp,cale);
		 directoare++;

		 //for(i = 0; i < tab; i++)
		//	printf("  ");

		// printf("%s\n", pDe->d_name);

		 //if(cale[strlen(cale) - 1] != '/')
         		 //strcat(cale,"/");
		 
		 //strcat(caleTemp,pDe->d_name);
		 //for(i = 0; i < tab; i++)
			//printf("  ");
		 tab++;
	         tree(specificator);
		 tab--;
		}
	  else
		{
		 //for(i = 0; i < tab; i++)
		//	printf("  ");
		// printf("%s\n", pDe->d_name);
		 fisiere++;
		}
	}

   return 0;
}

int main(int argc, char *argv[]){

   if(access(argv[1],F_OK) == 0)
	printf("%s\n",argv[1]);
   else
	{
	  perror(argv[1]);
	  return 1;
	}

   tree(argv[1]);

printf("\n%d directoare, %d fisiere\n",directoare, fisiere);

return 0;
}

