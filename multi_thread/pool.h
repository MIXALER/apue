#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>


typedef struct task
{
    void *(*run)(void *arg);

    void *arg;
    struct task *next;
} task_t;

typedef struct condition
{
    pthread_mutex_t pmutex;
    pthread_cond_t pcond;
} condition_t;

typedef struct threadpool
{
    condition_t ready;
    task_t *first;
    task_t *last;
    int counter;
    int idle;
    int max_threads;
    int quit;
} threadpool_t;


int condition_init(condition_t *cond);

int condition_lock(condition_t *cond);


int condition_unlock(condition_t *cond);

int condition_wait(condition_t *cond);

int condition_timewait(condition_t *cond, const struct timespec *abstime);


int condition_signal(condition_t *cond);

int condition_broadcast(condition_t *cond);

int condition_destory(condition_t *cond);

void *thread_routine(void *arg);

void threadpool_init(threadpool_t *pool, int threads);

void threadpool_add_task(threadpool_t *pool, void *(*run)(void *arg), void *arg);

void threadpool_destroy(threadpool_t *pool);