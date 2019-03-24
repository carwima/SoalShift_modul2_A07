#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
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

  while(1) {
    // main program here
  char *ptrToSubString, *ptrToSubString2;
      char fileName[100], newFile[100], path_awal[150], path_akhir[150] ;
      strcpy(path_awal, "/home/carwima/modul2/gambar/");
      strcpy(path_akhir, "/home/carwima/modul2/gambar/");
      DIR *dir;
      struct dirent *ent;
      dir = opendir("/home/carwima/modul2/gambar");
 //     if (dir != NULL) {
              while((ent = readdir(dir)) != NULL) {
                     strcpy(fileName,ent->d_name);
                     ptrToSubString = strstr(fileName,".png");
                     if (ptrToSubString != NULL && ent->d_type==DT_REG) {
                         printf("%s",ent->d_name);
                         ptrToSubString2 = strstr(fileName, "_grey.png");
                         if(ptrToSubString2 != NULL)
                             continue;
                         else{       


                           
                             strtok(fileName,".png");
                             strcpy(newFile,fileName);
                             strcat(newFile,"_grey.png");
                             strcat(fileName,".png");
                             strcat(path_awal,fileName);
                             strcat(path_akhir,newFile);
                             rename(path_awal,path_akhir);
                          }
                    } else {
                        continue;
                    }
              }
              closedir(dir);
/*      } else {
              perror("");
              return 5;
   }
    sleep(30);
*/  }
  exit(EXIT_SUCCESS);
}
