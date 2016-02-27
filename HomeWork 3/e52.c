//Program emitator

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int nrSemnale = 0;
pid_t pid;
sigset_t multimeSemnale;
struct sigaction act;

void handler(int n){
  printf("Am trimis %d semnale SIGUSR1\n",nrSemnale);
  exit(0);
}

void hRaspuns(int n){}

int main(){
 int i;
  
 act.sa_flags = 0;
 sigemptyset(&act.sa_mask);

 act.sa_handler = handler;
 sigaction(SIGINT,&act,NULL);
 
 act.sa_handler = hRaspuns;
 sigaction(SIGUSR1,&act,NULL);
 
 sigemptyset(&multimeSemnale); 
 sigaddset(&multimeSemnale,SIGUSR1);
 sigaddset(&multimeSemnale,SIGINT);
 sigprocmask(SIG_SETMASK,&multimeSemnale,NULL); 

 printf("PID Emitator: %d\n",getpid());
 printf("PID Receptor: "); scanf("%d",&pid);

 //sigemptyset(&multimeSemnale);
 sigfillset(&multimeSemnale);
 sigdelset(&multimeSemnale,SIGINT);
 sigdelset(&multimeSemnale,SIGUSR1);

 while(1){
    kill(pid,SIGUSR1);
    nrSemnale++;
    sigsuspend(&multimeSemnale);
 }
 
 return 0;
}
