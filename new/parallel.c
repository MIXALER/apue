#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <memory.h>


typedef struct matrix
{
    int **a;
    int **b;
    int **c;
} NMatrix;


typedef struct param
{
    NMatrix *p_matrix;
    int row;
    int col;
    int size;
} Param;


void func(Param *param)
{
    int row = param->row;
    int col = param->col;
    int ans = 0;

    for (int i = 0; i < param->size; ++i)
    {
        ans += param->p_matrix->a[row][i] * param->p_matrix->b[i][col];
    }
    param->p_matrix->c[row][col] = ans;
}

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
    int matrix_size = atoi(argv[1]);
    int n_times = atoi(argv[2]);

    for (int size = 2; size <= matrix_size; ++size)
    {
        pthread_t **threads = MALLOC(size, pthread_t *);
        NMatrix matrixs;
        matrixs.a = MALLOC(size, int *);
        matrixs.b = MALLOC(size, int *);
        matrixs.c = MALLOC(size, int *);
        Param **param = MALLOC(size, Param *);
        for (int i = 0; i < size; ++i)
        {
            threads[i] = MALLOC(size, pthread_t);
            matrixs.a[i] = MALLOC(size, int);
            matrixs.b[i] = MALLOC(size, int);
            matrixs.c[i] = MALLOC(size, int);
            param[i] = MALLOC(size, Param);
        }
        srand(time(NULL));   // 通过时间初始化随机种子
        for (int time = 0; time < n_times; ++time)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    matrixs.a[i][j] = rand() % 10;
                    matrixs.b[i][j] = rand() % 10;
                    matrixs.c[i][j] = 0;
                }
            }
            clock_t start = clock();
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; ++j)
                {
                    param[i][j].row = i;
                    param[i][j].col = j;
                    param[i][j].size = size;
                    param[i][j].p_matrix = &matrixs;
                    pthread_create(&threads[i][j], NULL, (void *) func, &param[i][j]);
                }
            }
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    pthread_join(threads[i][j], NULL);
                }
            }
            clock_t finish = clock();
            total_time += (double) (finish - start);
//            print((const int **)matrixs.a, size);
//            print((const int **)matrixs.b, size);
//            print((const int **)matrixs.c, size);
        }
        for (int i = 0; i < size; i++)
        {
            FREE(matrixs.a[i]);
            FREE(matrixs.b[i]);
            FREE(matrixs.c[i]);
            FREE(param[i]);
            FREE(threads[i]);
        }
        FREE(matrixs.a);
        FREE(matrixs.b);
        FREE(matrixs.c);
        FREE(param);
        FREE(threads);

        FILE *fd;
        fd = fopen("./parallel_log.txt", "a");
        fprintf(fd, "Matrix Size = %d  -----Average Runtime of %d times = %.10f\n", size, n_times,
                (double) (total_time / n_times) / CLOCKS_PER_SEC);
        fclose(fd);
        total_time = 0;
    }
    return 0;
}