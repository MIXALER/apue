//
// Created by yuanh on 2021/4/5.
//

#include "fcntl.h"
#include "unistd.h"
#include "stdio.h"
#include <errno.h>
#include <string.h>


int main()
{
    int fd = open("./test.cx",O_RDONLY); // 成功返回一个整数

    printf("fd: %d, errno=%d, %s\n", fd, errno, strerror(errno));
    close(fd);
    return 0;
}