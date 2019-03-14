# SoalShift_modul2_A07
<br>
#No 1
  
#No 2
  
#No 3
  
#No 4
  
#No 5
Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

##Ans:
5a. Untuk mengerjakan ini, kita menggunakan daemon agar bisa eksekusi program secara otomatis tanpa menggunakan crontab. lalu, kita menggunakan nama folder dengan fungsi time.h lalu disini kita menggunakan count. kalau count yang dimod 30 itu sema dengan 0, maka file akan membuat folder baru. Setelah itu program akan membuat file dan mengkopi dari log.
###source code:
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

Saynagnya, program no. 5a ini bertujuan untuk membunuh komputer secara perlahan. Karena itu dibutuhkan jawaban untuk soal no. 5b. Untuk soal no. 5b, kita hanya memakai exec untuk mengkill program yang sudah dibuat 5a.

<pre  style="font-family:arial;font-size:12px;border:1px dashed #CCCCCC;width:99%;height:auto;overflow:auto;background:#f0f0f0;;background-image:URL(http://2.bp.blogspot.com/_z5ltvMQPaa8/SjJXr_U2YBI/AAAAAAAAAAM/46OqEP32CJ8/s320/codebg.gif);padding:0px;color:#000000;text-align:left;line-height:20px;"><code style="color:#000000;word-wrap:normal;"> #include &lt;sys/wait.h&gt;  
 #include &lt;sys/types.h&gt;  
 #include &lt;unistd.h&gt;  
 #include &lt;string.h&gt;  
 int main(){  
   char *argv[] = {"pkill", "soal5a", NULL};  
   execv("/usr/bin/pkill", argv);  
 }  
</code></pre>
