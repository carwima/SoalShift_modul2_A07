#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    pid_t cid, cid1, cid2;
    int line[2],tes[2], status2, status3;
    pipe(line);
	if((cid1=fork())==0){
    		char *zip[] = {"unzip", "campur2.zip", NULL};
		execvp(zip[0], zip);
	}
	else{
		while ((wait(&status2)) > 0);
		if((cid2=fork())==0){
			dup2(line[1],1);
			close(line[0]);
                        close(line[1]);
			char *list[] = {"ls","/home/carwima/SoalShift_modul2_A07/soal3/campur2/", NULL};
        		execvp(list[0], list);
		}
		else{
			while((wait(&status3))>0);
			dup2(line[0],0);
			freopen ("daftar.txt","w",stdout);
			close(line[1]);
			char *grab[] = {"grep", ".txt$", NULL};
			execvp(grab[0], grab);
		}
        }

}
