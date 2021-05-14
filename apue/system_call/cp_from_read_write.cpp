//
// Created by yuanh on 2021/4/21.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char buf[1024];
    int n = 0;
    int fd1 = open(argv[1], O_RDONLY); // read
    if (fd1 == -1)
    {
        perror("open argv1 error");
        exit(1);
    }
    int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd2 == -1)
    {
        perror("open argv2 error");
        exit(1);
    }

    while ((n = read(fd1, buf, 1024) ) != 0)
    {
        if (n == -1)
        {
            perror("read  error");
            exit(1);
        }
        write(fd2, buf, n); //读多少，写多少
    }

    close(fd1);
    close(fd2);
    return 0;
}