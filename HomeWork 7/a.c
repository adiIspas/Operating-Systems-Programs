#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

 char x = '1';
 x++;
 write(STDOUT_FILENO,&x,sizeof(char));
 write(STDOUT_FILENO,&x,sizeof(char));
 write(STDOUT_FILENO,&x,sizeof(char));

 return 0;
}
