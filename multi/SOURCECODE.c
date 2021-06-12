#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // openmp 并行计算库
#include <time.h>

/*--------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

    int i, j;
//	初始话二维指针，用来保存两个相乘的矩阵和结果矩阵
    int **a;
    int **b;
    int **c;
//	运行时间
    double total_time;
    double start;

    /* Get number of threads and the size of multi_thread, repectively */
    int thread_count = strtol(argv[1], NULL, 10); // 从命令行参数中获取线程数量
    int size_matrix = atoi(argv[2]); // 获取矩阵的阶数

    /* Dynamic allocation for matrices */
    a = (int **) malloc(size_matrix * sizeof(int *));   // 给二维指针在堆区分配空间，用来存放具体的元素
    b = (int **) malloc(size_matrix * sizeof(int *));
    c = (int **) malloc(size_matrix * sizeof(int *));

    for (i = 0; i < size_matrix; i++)
    {
        a[i] = (int *) malloc(size_matrix * sizeof(int));  // 上面分配的是一维数组的空间，现在是分配的是每个一维空间的大小
        b[i] = (int *) malloc(size_matrix * sizeof(int));
        c[i] = (int *) malloc(size_matrix * sizeof(int));
    } /* endfor */


    srand(time(NULL));   // 通过时间初始化随机种子
    // 	/* Opens parallel zone */
    // 下面一段为 openmp 的并行计算编程范式，而且这里是 windows 平台的 下面那个 # pragma 是预处理器指令详细介绍可以参考：
    // https://blog.csdn.net/weixin_39640298/article/details/84503428 这篇博客， 这里 openmp 编程范式不是重点。我主要讲解一下代码逻辑

# pragma omp parallel num_threads(thread_count) default(none) shared(a, b, c, start) private(i, j) firstprivate(size_matrix)
    {

        /* Fill matrices using all threads. Each thread fill a single line. */
        // 从下面这个 paraller for 循环开始，代码将由多个线程同时执行,
# pragma omp parallel for default(shared) firstprivate(size_matrix) private(i, j) shared(a, b, c)
// 首先是初始化  a, b, c 三个矩阵，a, b 矩阵为随机值， c 为 -1
        for (i = 0; i < size_matrix; i++)
        {
            for (j = 0; j < size_matrix; j++)
            {
                a[i][j] = rand() % 100;
                b[i][j] = rand() % 100;
                c[i][j] = -1;
            }
        }

# pragma omp single
        {
            start = omp_get_wtime(); // start clock only for calculation 计时
        }

        /* Just one thread creates the tasks */
# pragma omp single
        {
            for (i = 0; i < size_matrix; i++)
            {
                for (j = 0; j < size_matrix; j++)
                {
                    /* One task for each element on C multi_thread*/
# pragma omp task firstprivate(i, j)
//                    显然这里这个三重循环是计算 a * b = c 的过程。

                    {
                        int k, mult_result = 0;
                        for (k = 0; k < size_matrix; k++)
                        {
                            mult_result += a[i][k] * b[k][j];
                        }
                        c[i][j] = mult_result;
                    } /* End task */
                }
            }
        } /* End single */
    }
    /* End parallel zone */
// 上面这段代码将一个矩阵乘法 映射到 openmp 的线程空间进行计算的，其中的难点是如何设置数据属性，就是上面的 private, 这个需要由线程同步的基础。

    total_time = omp_get_wtime() - start;
// 下面是一个 文件操作，将用时记录下来，写入文件
    FILE *tempo;
    tempo = fopen("C:\\Users\\ROBOWALT\\Desktop\\quiz4\\omptime.txt", "a");
    fprintf(tempo, "Problem Size = %d ----- Thread number = %d ----- Runtime = %f\n", size_matrix, thread_count,
            total_time);
    fclose(tempo);

    return 0;
}