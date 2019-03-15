# SoalShift_modul2_A07
# No 1
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

## Ans :
Untuk mengerjakan soal ini, digunakan library c &lt;dirent.h>, hal ini bertujuan untuk mendapatkan nama-nama file pada sebuah directory. Kemudian nama file tersebut akan dicheck dengan strstr(filename, ".png") hal ini bertujuan untuk mencari nama file dengan ekstensi ".png", jika file tersebut ditemukan makan dipastikan kembali apakah file sudah berformat "xxx_grey.png", jika belum maka akan dilakukan penamaan file. 
<br/>
Proses penamaan file : 
<br/>1. Memotong nama file sampai ".png"
<br/>2. Menambahkan nama file dengan "_grey.png" dengan strcat(dest,src)
<br/>3. Mengganti nama file dengan function rename(src, dest)
<br>
Karena program akan dijalankan secara otomatis, maka program dimasukkan kedalam program daemon, sehingga program akan berjalan secara terus menerus. Sampai setidaknya proses di kill.
<pre  style="font-family:arial;font-size:12px;border:1px dashed #CCCCCC;width:99%;height:auto;overflow:auto;background:#f0f0f0;;background-image:URL(http://2.bp.blogspot.com/_z5ltvMQPaa8/SjJXr_U2YBI/AAAAAAAAAAM/46OqEP32CJ8/s320/codebg.gif);padding:0px;color:#000000;text-align:left;line-height:20px;"><code style="color:#000000;word-wrap:normal;">#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;errno.h&gt;
#include &lt;unistd.h&gt;
#include &lt;syslog.h&gt;
#include &lt;string.h&gt;
#include &lt;dirent.h&gt;
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

  if (sid &lt; 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) &lt; 0) {
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
                     strcpy(fileName,ent-&gt;d_name);
                     ptrToSubString = strstr(fileName,".png");
                     if (ptrToSubString != NULL) {
                         printf("%s",ent-&gt;d_name);
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

</pre>
# No 2
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab
<br>
## Ans :

Cara mengerjakan :
<p>1. Menangkap array informasi tentang file elen.ku dengan stat(path, stat*)
<p>2. Mengambil informasi nama dan group dari file elen.ku dengan library &lt;pwd.h> dan &lt;grp.h>
<p>3. Mengecek apakah nama dan grup dari file merupakan www-data
<p>4. Jika step3 benar, maka file akan diganti moderatornya, dengan chmod(namafile,int) dengan int harus bilangan okta, maka di set dengan strtol(0,mode[],8). Pada mode di set [0777] maksud dari 0 di mode[0] adalah char bebas sebelum angka mod file.
<p>5. File di remove
<p>6. Karena diminta program secara otomatis setiap 3s, maka program diletakan pada program daemon dan ditambahkan sleep(3) atau memberi jeda 3s setiap runnya.

<pre  style="font-family:arial;font-size:12px;border:1px dashed #CCCCCC;width:99%;height:auto;overflow:auto;background:#f0f0f0;;background-image:URL(http://2.bp.blogspot.com/_z5ltvMQPaa8/SjJXr_U2YBI/AAAAAAAAAAM/46OqEP32CJ8/s320/codebg.gif);padding:0px;color:#000000;text-align:left;line-height:20px;"><code style="color:#000000;word-wrap:normal;">#include &lt;sys/types.h>
#include &lt;sys/stat.h>
#include &lt;stdio.h>
#include &lt;stdlib.h>
#include &lt;fcntl.h>
#include &lt;errno.h>
#include &lt;unistd.h>
#include &lt;syslog.h>
#include &lt;string.h>
#include &lt;pwd.h> //passwd / user
#include &lt;grp.h> //group

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
   stat(helen, &info);  //get hellen stat to char info
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
</pre>
# No 3
  
# No 4
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

## Ans

# No 5
Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

## Ans:
Untuk mengerjakan ini, kita menggunakan daemon agar bisa eksekusi program secara otomatis tanpa menggunakan crontab. lalu, kita menggunakan nama folder dengan fungsi time.h lalu disini kita menggunakan count. kalau count yang dimod 30 itu sema dengan 0, maka file akan membuat folder baru. Setelah itu program akan membuat file dan mengkopi dari log.<br>
Ini adalah Source code untuk no. 5a:<br>
<pre  style="font-family:arial;font-size:12px;border:1px dashed #CCCCCC;width:99%;height:auto;overflow:auto;background:#f0f0f0;;background-image:URL(http://2.bp.blogspot.com/_z5ltvMQPaa8/SjJXr_U2YBI/AAAAAAAAAAM/46OqEP32CJ8/s320/codebg.gif);padding:0px;color:#000000;text-align:left;line-height:20px;"><code style="color:#000000;word-wrap:normal;">   #include &lt;sys/types.h&gt;  
   #include &lt;sys/stat.h&gt;  
   #include &lt;stdio.h&gt;  
   #include &lt;stdlib.h&gt;  
   #include &lt;fcntl.h&gt;  
   #include &lt;errno.h&gt;  
   #include &lt;unistd.h&gt;  
   #include &lt;syslog.h&gt;  
   #include &lt;string.h&gt;  
   #include &lt;time.h&gt;  
 /*  
 char *SetCurrentDateTime(){
   time_t t=time(0) ;   
   struct tm *tmp ;   
   char line[80];   
   tmp=localtime(&amp;t);  
   strftime(line, sizeof(line), "%d:%m:%Y-%H-%M", tmp);   
   return line;   
 }  
 */  
 int main() {  
   int count=0;  
   pid_t pid, sid;  
   pid = fork();  
   if (pid &lt; 0) {  
     exit(EXIT_FAILURE);  
   }  
   if (pid &gt; 0) {  
     exit(EXIT_SUCCESS);  
   }  
   umask(0);  
   sid = setsid();  
   if (sid &lt; 0) {  
     exit(EXIT_FAILURE);  
   }  
   if ((chdir("/")) &lt; 0) {  
     exit(EXIT_FAILURE);  
   }  
   close(STDIN_FILENO);  
   close(STDOUT_FILENO);  
   close(STDERR_FILENO);  
   while(1) {  
 /*   FILE *fc;  
     fc=fopen("hehe.txt","w");  
 */   time_t t2=time(0) ; //buat nama folder yang ada  
     struct tm *tmp ;   
     char line[80];   
     tmp=localtime(&amp;t2);  
     strftime(line, sizeof(line), "%d:%m:%Y-%H-%M", tmp);   
     char path[100], t[100];  
     if(count%30==0){ //if digunakan untuk membuat folder  
       strcpy(t, line);  
       strcpy(path,"/home/honesta/log/");  
       strcat(path, t);  
       strcat(path, "/");  
       mkdir(path, 0777);  
     }  
     //yang inidigunakan untuk membuat file  
     int no = count+1;  
     char str[10];  
     strcpy(str, "");  
     sprintf(str, "log%d",no);  
     strcat(str,".log");  
     char strfinal[100];  
     strcpy(strfinal, path);  
     strcat(strfinal,str);  
 //    rename("/var/log/syslog", path);  
     // ini untuk membuat file log1.log dan selanjutnya  
     FILE *fc, *fs;  
     int c;  
     fc=fopen("/var/log/syslog", "r");  
     fs=fopen(strfinal,"w");  
     while(1){  
       c=fgetc(fc);  
       if(feof(fc)){  
         break;  
       }  
       fputc(c, fs);  
     }  
     fclose(fc);  
     fclose(fs);  
     sleep(60);  
     count++; //count ini sangat berguna di if  
   }  
   exit(EXIT_SUCCESS);  
 }  
</code></pre>

Sayangnya, program no. 5a ini bisa membunuh komputer secara perlahan karena programnya infinite dan akan melakukannya terus-menerus sampai memorinya penuh. Karena itu dibutuhkan jawaban untuk soal no. 5b. Untuk soal no. 5b, kita hanya memakai exec untuk mengkill program yang sudah dibuat 5a.

<pre  style="font-family:arial;font-size:12px;border:1px dashed #CCCCCC;width:99%;height:auto;overflow:auto;background:#f0f0f0;;background-image:URL(http://2.bp.blogspot.com/_z5ltvMQPaa8/SjJXr_U2YBI/AAAAAAAAAAM/46OqEP32CJ8/s320/codebg.gif);padding:0px;color:#000000;text-align:left;line-height:20px;"><code style="color:#000000;word-wrap:normal;"> #include &lt;sys/wait.h&gt;  
 #include &lt;sys/types.h&gt;  
 #include &lt;unistd.h&gt;  
 #include &lt;string.h&gt;  
 int main(){  
   char *argv[] = {"pkill", "soal5a", NULL};  
   execv("/usr/bin/pkill", argv);  
 }  
</code></pre>
