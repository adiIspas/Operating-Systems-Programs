#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void merge(char *a, int st, int dr){

    int i, j, k;
    char *x = malloc((dr - st) * sizeof(char));

    // plecam cu i-ul din stanga, iar cu j-ul din dreapta atata timp cat mai avem elemente de adaugat
    for (i = st, j = (st + dr) / 2, k = 0; i < (st + dr) / 2 || j < dr; ){
        if((i < (st + dr) / 2 && a[i] < a[j]) || j >= dr)
            x[k++] = a[i++];
        else
            x[k++] = a[j++];
    }

    // copiem elemente in vectorul primit initial
    for (i = 0; i < dr - st; i++)
        a[st  + i] = x[i];

    free(x);
}

void merge_sort(char *a, int st, int dr){

    if (dr - st <= 1)
        return;
    int m = (st + dr) / 2;      // mijlocul vectorului

    int fius = -1;
    int fiud = -1;

    int status;

    // creem fiul din stanga
    fius = fork();

    if (fius < 0){
        perror("fork");
        exit(1);
     }

    // aplicam procedura pentru fiul din stanga
    if(fius == 0){
        merge_sort(a, st, m);
        exit(0);
	}
    else{
        // creem fiul din dreapta
        fiud = fork();
        if (fiud < 0){
            perror("fork");
            exit(1);
        }

        // aplicam procedura pentru fiul din dreapta
        if(fiud == 0){
            merge_sort(a, m, dr);
            exit(0);
        }
    }

    // asteptam fii
    waitpid(fius, &status, 0);
    waitpid(fiud, &status, 0);

    merge(a, st, dr);   
}

int main () {

    int i, n = 0;
    char ch, *a = NULL;

    char *shm_array;    // pointer catre zona de memorie partajata
	int shm_id;         // identificatorul intern al zonei de memorie partajata
	key_t key;          
	size_t shm_size;    // dimensiunea zonei de memorie partajata

    FILE *input = fopen("in.txt","r");
    while(fscanf(input, "%c", &ch) != EOF){
        //if(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')
        {
            ++n;
            a = (char *)realloc(a, n * sizeof(char));
            a[n - 1] = ch;
        }
	}
    fclose(input);

    // vom folosi IPC_PRIVATE deoarce ne intereseaza sa fie utilizata exclusiv pentru procesul creator si descendentii acestuia
	key = IPC_PRIVATE;
	shm_size = n * sizeof(char);

    // obtinem identificatorul intern al IPC-ului
	if ((shm_id = shmget(key, shm_size, IPC_CREAT | 0666)) == -1) {
		perror("shmget");
		exit(1);
	}

    // facem operatiune de atasare pentru a putea folosi zona de memorie partajata
	if ((shm_array = shmat(shm_id, NULL, 0)) == (char *)-1) {
		perror("shmat");
		exit(1);
	}

    // copiem datele in zona de memorie partajata
	for (i = 0; i < n; i++)
		shm_array[i] = a[i];

     // vectorul inainte de sortare
     printf("INAINTE:\n");
     for (i = 0; i < n; i++)
        printf("%c ", shm_array[i]);
     printf("\n");
     merge_sort(shm_array, 0, n);

    // vectorul dupa sortare
    printf("DUPA:\n");
    for (i = 0; i < n; i++)
        printf("%c ", shm_array[i]);
    printf("\n");

    return 0;
}

