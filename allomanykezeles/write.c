#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    
    int fd; // fájl leíró

    if(argc < 2) 
    {
        printf("usage: %s filename\n", argv[0]);
        return 1; // visszatérési érték: hiba történt
    }
    
    fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644); // 0: oktális: 644: tulajdonosnak írás-olvasás
    
    if(fd < 0)
    {
        perror("open"); // hiba esetén: open HIBA ÜZENET
        return 1; // visszatérési érték: hiba történt
    }
    
    if(write(fd, "Hello Vilag!\n", 13) != 13)
    {
        perror("write");
        return 1;
    }
    
    close(fd);
    
    return 0;
}
