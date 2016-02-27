#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

 char x, y, z, sp = ' ', end = '\n';

 read(STDIN_FILENO,&x,sizeof(char));
 read(STDIN_FILENO,&y,sizeof(char));
 read(STDIN_FILENO,&z,sizeof(char));

 write(STDOUT_FILENO,&x,sizeof(char));
 write(STDOUT_FILENO,&sp,sizeof(char));
 write(STDOUT_FILENO,&y,sizeof(char));
 write(STDOUT_FILENO,&sp,sizeof(char));
 write(STDOUT_FILENO,&z,sizeof(char));
 write(STDOUT_FILENO,&end,sizeof(char));

 return 0;
}
