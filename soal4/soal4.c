#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/sysmacros.h>
int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  int ctr=1;
  while(1) {
    // main program here
   char makanEnak[]="/home/carwima/makanan/makanenak.txt";
   struct stat info;
   stat(makanEnak,&info);
   time_t now;
   time(&now);
   int beda;
/*   FILE *fi;
   fi=fopen(makanEnak,"w");
   fclose(fi);
*/   beda = difftime(now, info.st_atime); 
   if(beda<=30){ 
     printf("atime :  %d  ",beda); //debug
     char path[150],str[20];
     strcpy(path, "/home/carwima/makanan/makan_sehat");
     sprintf(str,"%d.txt",ctr);
     strcat(path,str);
     FILE *baru;
     baru = fopen(path,"w");
     fclose(baru);
     ctr++;
     sleep(5);
     }
//     sleep(1);
  }
  exit(EXIT_SUCCESS);
}
