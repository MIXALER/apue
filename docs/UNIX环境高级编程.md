## 1 UNIX 系统基础知识

### 1.1 引言



## 2 UNIX 标准及实现

## 3 文件 I/O

UNIX系统中的大多数文件I/O只需用到5个函数：open、read、write、lseek 以及 close。然后说明不同缓冲长度对 read 和 write 的影响。

本章描述的函数经常被称为不带缓冲的 I/O。不带缓冲指的是每个 read 和 write 都调用内核中的一个系统调用。

只要涉及在多个进程间共享资源，原子操作的概念就变得非常重要。

### 3.1 文件描述符

对于内核而言，所有打开的文件都通过**文件描述符引用**。文件描述符是一个非负整数。当**打开一个现有文件**或创建一个新文件时，**内核向进程**返回一个文件描述符。当读、写一个文件时，使用 open 或 creat 返回的文件描述符**标识该文件**，将其作为参数传送给read或write。

按照惯例，UNIX 系统 shell 把文件描述符 0 与进程的标准输入关联，文件描述符 1 与标准输出关联，文件描述符 2 与标准错误关联。这是各种 shell以及很多应用程序使用的惯例，与UNIX内核无关。

unistd.h 中定义

```c
/* Standard file descriptors.  */
#define    STDIN_FILENO   0  /* Standard input.  */
#define    STDOUT_FILENO  1  /* Standard output.  */
#define    STDERR_FILENO  2  /* Standard error output.  */
```

### 3.2 open ， openat， creat  函数

#include <fcntl.h>

```c
   int open(const char *pathname, int flags);
   int open(const char *pathname, int flags, mode_t mode);

   int creat(const char *pathname, mode_t mode);

   int openat(int dirfd, const char *pathname, int flags);
   int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

### 3.3 close 函数

#include <unistd.h>

```c
   int close(int fd);
```

关闭一个文件的时候，还会释放该进程加在该文件上的所有记录锁。

### 3.4 lseek 函数

重点！每个打开文件都有一个与其相关联的“当前文件偏移量”（current file offset）。它通常是一个非负整数，用以度量从文件开始处计算的字节数（本节稍后将对“非负”这一修饰词的某些例外进行说明）。通常，读、写操作都从当前文件偏移量处开始，并使偏移量增加所读写的字节数。按系统默认的情况，当打开一个文件时，除非指定O_APPEND选项，否则该偏移量被设置为0。

可以调用lseek显式地为一个打开文件设置偏移量。

off_t lseek(int fd, off_t offset, int whence);

参数：fd: 文件描述符



### 3.5 read，write 函数

```c++
#include <unistd.h>

   ssize_t write(int fd, const void *buf, size_t count);
```

```c++
#include <unistd.h>

   ssize_t read(int fd, void *buf, size_t count);
```

参数：

-   fd 文件描述符
-   buf 存数据的缓冲区和待写出的缓冲区
-   count 缓冲区的大小和数据大小

返回值

-   成功：读到的字节数，写入的字节数，0表示读到文件末尾
-   失败 -1 并设置 errno = EAGIN 或 EWOULDBLOCK ，说明而是read以非阻塞方式在读一个网络文件或设备文件，且文件无数据

## 5 标准 I/O 库

标准I/O库处理很多细节，如缓冲区分配、以优化的块长度执行I/O等。这些处理使用户不必担心如何选择使用正确的块长度（如3.9节中所述）。这使得它便于用户使用，但是如果我们不深入地了解I/O库函数的操作，也会带来一些问题。

### 5.1 流和 FILE 对象

在第3章中，所有 I/O 函数都是围绕**文件描述符**的。当打开一个文件时，即**返回一个文件描述符**，然后该文件描述符就用于后续的I/O操作。而对于标准I/O库，它们的操作是围绕**流（stream）**进行的，当用标准 I/O 库打开或创建一个文件时，我们已使一个流与一个文件相关联。

当打开一个流时，标准 I/O 函数 fopen返回一个指向FILE对象的指针。该对象通常是一个**结构体**，它包含了标准I/O库为管理该流需要的所有信息，包括用于实际 I/O 的**文件描述符**、指向用于该流缓冲区的指针、缓冲区的长度、当前在缓冲区中的字符数以及出错标志等。

应用程序没有必要检验 FILE 对象。为了引用一个流，需将 FILE 指针作为参数传递给每个标准 I/O 函数。在本书中，我们称指向 FILE 对象的指针（类型为FILE*）为文件指针。

### 5.2 标准输入，标准输出和标准错误

对一个进程预定义了 3 个流，并且这 3 个流可以自动地被进程使用，它们是：标准输入、标准输出和标准错误。这些流引用的文件与在第三章 I/O 提到文件描述符 STDIN_FILENO、STDOUT_FILENO 和STDERR_FILENO所引用的相同。

这3个标准I/O流通过预定义文件指针stdin、stdout和stderr加以引用。这3个文件指针定义在头文件<stdio.h>中。

### 5.3 缓冲

重点！难点！待学习！

### 5.4 打开流，fopen, freopen, fdopen 函数

#include <stdio.h>

```c
   FILE *fopen(const char *path, const char *mode);

   FILE *fdopen(int fd, const char *mode);

   FILE *freopen(const char *path, const char *mode, FILE *stream);
```

这3个函数的区别如下。

（1）fopen 函数打开路径名为 path 的一个指定的文件。

（2）freopen 函数在一个指定的流上打开一个指定的文件，如若该流已经打开，则先关闭该流。若该流已经定向，则使用 freopen 清除该定向。此函数一般用于将一个指定的文件打开为一个预定义的流：标准输入、标准输出或标准错误。

（3）fdopen 函数取一个已有的文件描述符（我们可能从 open、dup、dup2、fcntl、pipe、socket、socketpair 或accept 函数得到此文件描述符），并使一个标准的 I/O 流与该描述符相结合。此函数常用于由创建管道和网络通信通道函数返回的描述符。因为这些特殊类型的文件不能用标准 I/O 函数 fopen 打开，所以我们必须先调用设备专用函数以获得一个文件描述符，然后用 fdopen 使一个标准 I/O 流与该描述符相结合。

### perror函数

void perror(const char*)

错误提示函数，能输出具体的错误信息



### strace 命令

跟踪程序执行过程中所用到的系统调用和信号



### 文件描述符

PCB 进程控制块， 本质 结构体

成员， 文件描述符 ，0/1/2/3/4 /... /1023

其实每个文件描述符对应的也是一个结构体，被操作系统隐藏。

为什么fd为3呢

0 为 STDIN_FILENO 1 为STDOUT_FILENO 2 为STDERR_FILENO

一个进程最多能打开1024个文件，每次打开都是可用的最小的那个

### 阻塞，非阻塞

是设备文件，网络文件的属性

读常规文件是不会阻塞的

读设备文件，读网络文件

/dev/tty -- 终端文件

open("/dev/tty", O_RDWR | O_NONBLOCK) 设置为非阻塞

### fcntl 函数

改变一个**已经打开文件**的访问控制属性

### fork 函数

创建一个子进程

#include <unistd.h>   posix 标准定义的 unix 类系统定义符号常量的头文件，包含了许多 UNIX 系统服务的函数原型

pid_t fork(void);

函数通过复制调用进程的方式创建一个新的进程，新的进程称为子进程，调用进程称为父进程。

如果调用成功，返回子进程的 PID 给父进程。如果调用失败，返回 -1，并设置 errno 











