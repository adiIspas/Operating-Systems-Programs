#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

 char x;

 read(STDIN_FILENO,&x,sizeof(char));
 x++;
 write(STDOUT_FILENO,&x,sizeof(char));
 system("./d");
 system("./e");

 return 0;
}
