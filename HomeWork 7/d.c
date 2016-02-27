#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

 char x;

 read(STDIN_FILENO,&x,sizeof(char));
 x = x + 3;
 write(STDOUT_FILENO,&x,sizeof(char));
 return 0;
}
