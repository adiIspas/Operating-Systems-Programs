#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct nod
{
  int info;
  struct nod *stanga;
  struct nod *dreapta;
}*cap;

void sterge_arbore(struct nod* cap)
{
  if(cap != 0)
  {
      sterge_arbore(cap -> stanga);
      sterge_arbore(cap -> dreapta);
      free(cap);
  }
}

struct nod* nodNou(int info){

    struct nod* nod = (struct nod*)malloc(sizeof(struct nod));
    nod -> info = info;
    nod -> stanga = NULL;
    nod -> dreapta = NULL;

    return nod;
}

void adauga(int info, struct nod* cap){

    struct nod* nodAnterior = NULL;
    struct nod* nodCurent = cap;
    char tipNod = ' ';

    while(nodCurent){
        nodAnterior = nodCurent;

        if(info < nodCurent -> info){
            nodCurent = nodCurent -> stanga;
            tipNod = 'S';
        }
        else{
            nodCurent = nodCurent -> dreapta;
            tipNod = 'D';
        }
    }

    if(tipNod == 'S')
        nodAnterior -> stanga = nodNou(info);
    else
        nodAnterior -> dreapta = nodNou(info);
}

void BFS(struct nod* cap)
{
    struct nod* x;
    int scrieri = 0;

    int d[2];
    pipe(d);

    write(d[1], &cap, sizeof(cap));
    scrieri++;

    while(scrieri > 0 && read(d[0], &x, sizeof(x)) > 0){

        scrieri--;
        printf("%d ",x -> info);

        if(x -> stanga!=0){
            write(d[1],&x->stanga,sizeof(x));
            scrieri++;
        }

        if(x -> dreapta!=0){
            write(d[1],&x->dreapta,sizeof(x));
            scrieri++;
        }
    }

    close(d[0]);
    close(d[1]);
}

int main()
{
    struct nod* nod;
    int i = 0, nrNoduri, info;
    printf("Numar noduri: ");
    scanf("%d",&nrNoduri);

    printf("Nod %d: ", i + 1);
    scanf("%d", &info);
    cap = nodNou(info);

    for(i = 1; i < nrNoduri; i++){
        printf("Nod %d: ", i + 1);
        scanf("%d", &info);
        adauga(info,cap);
    }

    printf("Parcurgere in latime: ");
    BFS(cap);
    printf("\n");
    sterge_arbore(cap);

    return 0;
}
