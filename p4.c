#include <stdio.h>
#include <time.h>
int main(  ) 
{
  int length, i = 0, wd;
  int fd;
	
    time_t timer;
    char buffer[25];
    char *s=NULL;
    struct tm* tm_info;

//char  *time1 = DateTime.Now.ToShortTimeString();
  //char buffer[BUF_LEN];
  FILE *fk;
  //char buffer[EVENT_BUF_LEN];
  char str1[] = "File has been updated! ";
  char str2[] = "This is tutorialspoint.com2";
  char str3[] = "This is tutorialspoint.com3";

    time(&timer);
    tm_info = localtime(&timer);
    strptime(buffer, 25, "%Y:%m:%d %H:%M:%s", tm_info);

   fk = fopen( "/home/technoworld/Desktop/file.txt" , "w" );

  	for(i=0;i<5;i++){
		//delay(1000);
	      fprintf(fk,"%s   %s  %c",str1, buffer, '\n');
}
		fprintf(fk,"%s",buffer);
      
  fclose( fk );
  
  return 0;
}
