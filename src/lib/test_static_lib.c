//
// Created by yuanh on 2021/4/4.
//

#include "stdio.h"

int main()
{
    int a=3, b=2;
    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, sub(a, b));
    printf("%d * %d = %d\n", a, b, multiply(a, b));
    printf("%d / %d = %d\n", a, b, div(a, b));
    return 0;

}