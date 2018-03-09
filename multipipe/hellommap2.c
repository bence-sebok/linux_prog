#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
  int fd;
  char* mem;
  
  if(argc != 2)
  {
    printf("Használat: %s állomány\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  if((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) < 0)
  {
    perror("open");
    return EXIT_FAILURE;
  }

  // Feltöltjük a megadott méretig, hogy legyen mit mappelni.
  ftruncate(fd, 256);
  
  mem = mmap(NULL, 256, PROT_WRITE, MAP_SHARED, fd, 0);
  if(mem == MAP_FAILED)
  {
      perror("mmap");
      return EXIT_FAILURE;
  }

  sprintf(mem, "Hello mmap!\n");
  
  munmap(mem, 256);
  
  close(fd);
  return EXIT_SUCCESS;
} 
