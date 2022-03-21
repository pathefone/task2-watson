#include <fcntl.h>	
#include <stdlib.h>	
#include <stdio.h>	
#include <string.h>	
#include <unistd.h>	
#include <syslog.h>


int only_one_instance(void)
{
	int fd;
	int rc = 0;
	struct flock lock, savelock;

	fd = open("/var/lock/procd_rutx-watson.lock", O_RDWR);
	if(fd < 0) {
		syslog(LOG_ERR, "Failed to access lock file");
		rc = -1;
	}

	lock.l_type    = F_WRLCK;   /* Test for any lock on any part of file. */
  	lock.l_start   = 0;
  	lock.l_whence  = SEEK_SET;
  	lock.l_len     = 0;  

  	savelock = lock;

  	fcntl(fd, F_GETLK, &lock);  /* Overwrites lock structure with preventors. */
  	if (lock.l_type == F_WRLCK)
  	{
     	printf("Process %ld has a write lock already!\n", lock.l_pid);
     	exit(1); // change and do cleanup before exiting
  	}
  	else if (lock.l_type == F_RDLCK)
  	{
     	printf("Process %ld has a read lock already!\n", lock.l_pid);
     	exit(1); // change and do cleanup before exiting
  	}
  	else
     	fcntl(fd, F_SETLK, &savelock);
  return rc;
}
