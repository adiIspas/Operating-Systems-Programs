// Program receptor

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include <setjmp.h>
#include<sys/types.h>
  
int nrSemnale=0; 
pid_t pid; 
sigset_t multimeSemnale;
struct sigaction act;
sigjmp_buf context;

void hAlarm(int n){
 kill(pid,SIGINT);
// siglongjmp(context,1); 
 //kill(pid,SIGINT);

 printf("Am primit %d semnale SIGUSR1\n",nrSemnale);
 kill(pid,SIGKILL);
 exit(0);
}

void hSignal(int n){
  nrSemnale++;

  /*sigemptyset(&multimeSemnale);
  sigaddset(&multimeSemnale,SIGALRM);
  sigprocmask(SIG_UNBLOCK,&multimeSemnale,NULL); 
  sigprocmask(SIG_BLOCK,&multimeSemnale,NULL);*/

  kill(pid,SIGUSR1);
}

int main()
{
 act.sa_flags = 0;
 sigemptyset(&act.sa_mask);
 
 act.sa_handler = hSignal;
 sigaction(SIGUSR1, &act, NULL);
 
 sigemptyset(&act.sa_mask);
 sigaddset(&act.sa_mask,SIGALRM);
 
 act.sa_handler = hAlarm;
 sigaction(SIGALRM, &act, NULL);
 
 sigemptyset(&multimeSemnale); 
 sigaddset(&multimeSemnale,SIGUSR1);
 sigprocmask(SIG_SETMASK,&multimeSemnale,NULL); 

 printf("PID Receptor: %d\n",getpid());
 printf("PID Emitator: "); scanf("%d",&pid);
 
 sigemptyset(&multimeSemnale);
 sigfillset(&multimeSemnale); 
 sigdelset(&multimeSemnale,SIGUSR1); 
 sigdelset(&multimeSemnale,SIGALRM);
 
 alarm(4);

 //if(sigsetjmp(context,0) != 1)
 //{
  while(1)
   {
    sigsuspend(&multimeSemnale); 
   }
// }
// else
  //kill(pid,SIGINT);

// printf("Am primit %d semnale SIGUSR1\n",nrSemnale);
 //kill(pid,SIGKILL);

 return 0;
}
