#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int permutare[20], n, viz[20];

void solutie()
{
  int i;

  for(i = 1; i <= n; i++)
      printf("%d ", permutare[i]);
  printf("\n");
}

void back(int top)
{
  int i;
  if(top == n + 1)
     solutie(); 
  else
    {for(i = 1; i <=n; i++)
	if(!viz[i])
	{
          viz[i] = 1;
	  permutare[top] = i;
          if(!fork())
	  {
	    back(top + 1);
            exit(0);
   	  }
          else
             viz[i] = 0;
         //wait(NULL);
	}
   while(wait(NULL)!=-1);}
}

int main()
{   
    printf("N = ");
    scanf("%d",&n);
	
    printf("Waiting ... \n");
    back(1);
 
    printf("Done ... \n");
    
    return 0;
}

