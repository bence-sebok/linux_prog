#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>

int main(int argc, char* argv[])
{
  int fds[2];
  char buf[256];
  int len;
  int fdix;
  fd_set watchset;
  fd_set inset;
  int maxfd;
  
  fds[0] = open("pipe1", O_RDONLY | O_NONBLOCK);
  if(fds[0] < 0)
  {
    perror("open");
    return EXIT_FAILURE;
  }
  
  fds[1] = open("pipe2", O_RDONLY | O_NONBLOCK);
  if(fds[1] < 0)
  {
    perror("open");
    return EXIT_FAILURE;
  }
  
  FD_ZERO(&watchset);
  FD_SET(fds[0], &watchset);
  FD_SET(fds[1], &watchset);
  maxfd = fds[0] > fds[1] ? fds[0] : fds[1];
  
  while(1)
  {
    inset = watchset;
    if(select(maxfd + 1, &inset, NULL, NULL, NULL) < 0)
    {
      perror("select");
      return EXIT_FAILURE;
    }
    
    for(fdix = 0; fdix < 2; fdix++)
    {
      if(FD_ISSET(fds[fdix], &inset))
      {
	len = read(fds[fdix], buf, sizeof(buf));
	if(len == 0)
	{
	  printf("A pipe%d lezarult!\n", fdix + 1);
	  return EXIT_SUCCESS;
	}
	else if((len < 0) && (errno != EAGAIN))
	{
	  perror("read");
	  return EXIT_FAILURE;
	}
	else if(len > 0)
	{
	  write(STDOUT_FILENO, buf, len);
	}
      }
    }
  }
  
  close(fds[0]);
  close(fds[1]);
  
  return EXIT_SUCCESS;
}
