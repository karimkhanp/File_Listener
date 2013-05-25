#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>
#include <time.h>

#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME 20 /*Assuming that the length of the filename won't exceed 20 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*buffer to store the data of events*/
#define SIZE 20000
int main( int argc, char **argv ) 
{
	int length, i = 0, wd;
	int fd;
	char buffer[BUF_LEN];
    
	time_t timer;

	char buffer2[25];
	char *s=NULL;
	struct tm* tm_info;

	FILE *fk;
	//char buffer[EVENT_BUF_LEN];
	char str1[] = "File has been updated at time :";
    
	time_t now;
	struct tm *tm;

	/*now = time(0);
	if ((tm = localtime (&now)) == NULL) {
		printf ("Error extracting time stuff\n");
		return 1;
	} */
	
	fk = fopen( "/home/technoworld/Desktop/file.txt" , "w" );   

	/* Initialize Inotify*/
	fd = inotify_init();
	if ( fd < 0 ) {
		perror( "Couldn't initialize inotify");
	}

	/* add watch to starting directory */
	wd = inotify_add_watch(fd, argv[1], IN_MODIFY );   // Listen to Change in file. Same can done for Delete and create using 	IN_Modify and IN_CREATE
	if (wd == -1){
		printf("Couldn't add listen to %s\n",argv[1]);
	}
	else{
		printf("Listening: %s\n",argv[1]);
	}

	/* do it forever*/
	while(1){
	
		now = time(0);
		if ((tm = localtime (&now)) == NULL) {
			printf ("Error extracting time stuff\n");
			return 1;
		}
		
	      fk = fopen( "file.txt" , "a" );
	      i = 0;
	      length = read( fd, buffer, BUF_LEN );  

		if ( length < 0 ) {
		        perror( "read" );
	        }  

		while ( i < length ) {
			struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
			if ( event->len ) {         
			  if ( event->mask & IN_MODIFY){
				if (event->mask & IN_ISDIR)
			        printf( "The directory %s was modified.\n", event->name );       
		 	        else{
			        	printf( "The file %s was modified see log file for time stamp \n", event->name  ); 
			    		fprintf(fk,"%s %04d-%02d-%02d %02d:%02d:%02d %c",str1, tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,tm->tm_hour, tm->tm_min, tm->tm_sec , '\n');
			    	//Here time can be achieved in various format as per requirement
				}
			  }
			  
			i += EVENT_SIZE + event->len;
			}
     		 }
	fclose(fk);
	}

  /* Clean up*/
  inotify_rm_watch( fd, wd );
  close( fd );
  
  return 0;
}
