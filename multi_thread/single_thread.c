#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory.h>

#define MALLOC(n, type) \
        ((type *)malloc( (n) * sizeof(type)))

#define FREE(p)             \
        if(p!=NULL)         \
        {                   \
              free(p);       \
              p = NULL;     \
        }

void print(const int **a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    if (argc != 3)
    {
        printf("Usage: ./a.out matrix_size measurement_times\n");
        exit(0);
    }
    double total_time;
    int n_times = atoi(argv[1]);
    int matrix_size = atoi(argv[2]);
    int **a;
    int **b;
    int **c;
    for (int size = 2; size <= matrix_size; ++size)
    {
        /* Dynamic allocation for matrices */
        a = MALLOC(size, int *);
        b = MALLOC(size, int *);
        c = MALLOC(size, int *);
        for (int i = 0; i < size; i++)
        {
            a[i] = MALLOC(size, int);
            b[i] = MALLOC(size, int);
            c[i] = MALLOC(size, int);
        }
        srand(time(NULL));   // 通过时间初始化随机种子
        for (int time = 0; time < n_times; ++time)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    a[i][j] = rand() % 10;
                    b[i][j] = rand() % 10;
                    c[i][j] = 0;
                }
            }
            clock_t start = clock();
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    for (int k = 0; k < size; k++)
                        c[i][j] += a[i][k] * b[k][j];
            clock_t finish = clock();
            total_time += (double) (finish - start);
            print((const int **) a, size);
            print((const int **) b, size);
            print((const int **) c, size);
        }

        for (int i = 0; i < size; i++)
        {
            FREE(a[i]);
            FREE(b[i]);
            FREE(c[i]);
        }
        FREE(a);
        FREE(b);
        FREE(c);
        FILE *fd;
        fd = fopen("./single_thread_log.txt", "a");
        fprintf(fd, "Matrix Size = %d  -----Average Runtime of %d times = %.10f\n", size, n_times,
                (double) (total_time / n_times) / CLOCKS_PER_SEC);
        fclose(fd);
        total_time = 0;
    }
    return 0;
}

