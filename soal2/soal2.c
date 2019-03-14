#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h> //passwd / user
#include <grp.h> //group

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
   struct stat info;
   char helen[] = "/home/carwima/hatiku/elen.ku";
   stat(helen, &info);  // Error check omitted
   struct passwd *pw = getpwuid(info.st_uid); //passwd user
   struct group  *gr = getgrgid(info.st_gid); //group
//   printf("%s", gr->gr_name);  //was for checking group name
   if(strcmp(gr->gr_name,"www-data")==0 && strcmp(pw->pw_name, "www-data")==0){ //membandingkan string group
//        printf("true, bye-bye file!/n");
        char mode[] = "0777"; 
        int i;
        i = strtol(mode, 0, 8); //
        chmod(helen, i);
        remove("/home/carwima/hatiku/elen.ku");
    }
    sleep(3);
  }
  exit(EXIT_SUCCESS);
}
