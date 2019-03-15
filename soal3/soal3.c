#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    pid_t cid, cid1, cid2;
    int line[2], status;
    cid=fork();
    pipe(line);//pip pertama
    pipe(line+2);//pip kedua
    if (cid<0) {
        exit(EXIT_FAILURE);
    }
    else if (cid==0) {
            char *zip[] = {"unzip", "campur2.zip", NULL};
            execv(zip[0], zip); 
    }
    
    else
    {
        while(wait(&status)>0);
        cid1=fork();
        if (cid==0) {
            dup2(line[1],1);//buat menyimpan final ls nanti. Intinya buat write
            close(line[1]);
            close(line[0]);
            close(line[3]);
            close(line[2]);
            char *look={"ls","/home/honesta/Documents/sisop/SoalShift/modul2/soal3/campur2/", NULL};
            execv(look[0],look);
        }
        else
        {
            cid2=fork();
            if (cid2>0) {
                dup2(line[0],0);//ngebaca yang dari ls tadi
                dup2(line[3],1);//nyimpan final dari greb nanti
                close(line[3]);
                close(line[1]);
                close(line[2]);
                close(line[0]);
                char *g[]={"grep",".txt$",NULL};
                execvp(g[0],g);//ketika ada file yang paling belakang isinya.txt diambil
                //printf("hell");       
            }
            else
            {
                //wait(NULL);
                char final[1000];
                close(line[1]);
                close(line[0]);
                close(line[3]);
                read(line[2],final,sizeof(final));//ngebaca dari greb tadi
                close(line[2]);
                //printf("%s",final);
                FILE *file=fopen("/home/honesta/Documents/sisop/SoalShift/modul2/soal3/daftar.txt","w+");//buat file
                fputs(final,file);//memasukkan final ke file
                fclose(file);          
                //printf("%d",check);
            }
        }      
    }
}