#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    
    int fd; // fájl leíró
    
    char string[13 + 1];

    if(argc < 2) 
    {
        printf("usage: %s filename\n", argv[0]);
        return 1; // visszatérési érték: hiba történt
    }
    
    fd = open(argv[1], O_RDONLY); // 0: oktális: 644: tulajdonosnak írás-olvasás
    
    if(fd < 0)
    {
        perror("open"); // hiba esetén: open HIBA ÜZENET
        return 1; // visszatérési érték: hiba történt
    }
    
    if(read(fd, string, 13) != 13)
    {
        perror("read");
        return 1;
    }
    
    close(fd);
    
    string[12] = '\0';
    
    printf("%s\n", string);
    
    return 0;
}
