#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include<fcntl.h>

struct nod
{
  int info;
  struct nod *stanga;
  struct nod *dreapta;
};

typedef struct nod arbore;

void sterge_arbore(struct nod *cap)
{
  if(cap != 0)
  {
      sterge_arbore(cap->stanga);
      sterge_arbore(cap->dreapta);
      free(cap);
  }
}

void adauga(int info, struct nod **cap)
{
    if(*cap == 0)
    {
        *cap = (struct nod*) malloc(sizeof(struct nod));
        (*cap)->info = info;

        (*cap)->stanga = 0;    
        (*cap)->dreapta = 0;  
    }
    else if(info < (*cap)->info)
    {
        adauga(info, &(*cap)->stanga);
    }
    else if(info > (*cap)->info)
    {
        adauga(info, &(*cap)->dreapta);
    }
}

void BFS(arbore* cap)
{   
    arbore* x;
    
    int d[2];
    pipe(d);
    
    fcntl(d[0], F_SETFL, O_NONBLOCK);    

    write(d[1],&cap,sizeof(cap)); 

    while (read(d[0],&x,sizeof(x)) > 0)
        {
         printf("%d ",x->info);

         if(x->stanga!=0)
           write(d[1],&x->stanga,sizeof(x)); 
         if(x->dreapta!=0)
	   write(d[1],&x->dreapta,sizeof(x)); 
        }

    close(d[0]);
    close(d[1]);
}

int main()
{
    arbore *cap;
    int i, n, x;
    scanf("%d",&n);
    
    for(i = 0; i < n; i++){
	scanf("%d",&x);
        adauga(x,&cap);
    }
    
    printf("BFS: ");    
    BFS(cap);
    printf("\n"); 

    return 0;
}
