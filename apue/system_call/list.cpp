//
// Created by yuanh on 2021/3/26.
//

#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    DIR             	*dp;
    struct dirent   	*dirp;
    if(argc != 2)
    {
        printf("a single argument is required");
        return 1;
    }
    if((dp = opendir(argv[1])) == NULL)
    {
        printf("can't open %s", argv[1]);
        return 1;
    }
    while(( dirp = readdir(dp)) != NULL)
        printf("%s\n",dirp->d_name);
    closedir(dp);
    return 0;
}