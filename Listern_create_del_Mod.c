#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>

#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME 16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*buffer to store the data of events*/

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
  while(1)
    {
    
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
          if ( event->mask & IN_CREATE) {
            if (event->mask & IN_ISDIR)
              printf( "The directory %s was Created.\n", event->name );       
            else
              printf( "The file %s was Created with WD %d\n", event->name, event->wd );       
          }
          
          if ( event->mask & IN_MODIFY) {
            if (event->mask & IN_ISDIR)
              printf( "The directory %s was modified.\n", event->name );       
            else
              printf( "The file %s was modified with WD %d\n", event->name, event->wd );       
          }
          
          if ( event->mask & IN_DELETE) {
            if (event->mask & IN_ISDIR)
              printf( "The directory %s was deleted.\n", event->name );       
            else
              printf( "The file %s was deleted with WD %d\n", event->name, event->wd );       
          }  


          i += EVENT_SIZE + event->len;
        }
      }
    }

  /* Clean up*/
  inotify_rm_watch( fd, wd );
  close( fd );
  
  return 0;
}
