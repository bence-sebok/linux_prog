#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

int main()
{
  DIR * d;
  struct dirent* elem;
  struct stat st;
  
  if((d = opendir(".")) == NULL)
  {
      perror("opendir");
      return 1;
  }
  
  while((elem = readdir(d)) != NULL)
  {
    if(stat(elem->d_name, &st) < 0)
    {
        perror("stat");
        return 1;
    }
  
    printf("dev=%lu ", st.st_dev);
    printf("mode=%#7o ", st.st_mode);
    printf("uid=%4u ", st.st_uid);
    printf("gid=%4u ", st.st_gid);
    printf("size=%4zu ", st.st_size);
    printf("blksize=%zu ", st.st_blksize);
    printf("blocks=%2zu", st.st_blocks);
    printf(" %s\n", elem->d_name);
  }
  
  closedir(d);
  
  return 0;
}

