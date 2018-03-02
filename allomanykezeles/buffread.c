#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    char buff[256];
    int len;
    
    while((len = read(STDIN_FILENO, buff, sizeof(buff))) < 0)
    {
        if(write(STDOUT_FILENO, buff, len) < 0)
        {
            perror("write");
            return 1;
        }
    }
    
    if(len < 0)
    {
        perror("read");
        return 1;
    }
    
    return 0;
}
