# 高级I/O

> 内容简介：
>
> * 非阻塞I/O
> * 记录锁
> * I/O多路转接
> * 异步I/O
> * `readv`和`writev`函数
> * 存储映射I/O
>
> 以后要学习的内容(进程间通信等等)都需要用到这张记录的知识点，所以需要反复阅读

## 非阻塞I/O

之前的文章中，将系统调用分成了`低速系统调用`和`其他`。低速系统调用指的是：

* 如果某些文件类型的数据不存在，读操作可能会是调用者永远阻塞
* 如果数据不能被相同的文件类型立即接受，写操作可能使调用者永远阻塞
* 在某种条件发生之前打开某些文件类型可能会发生阻塞。
* 对已经加上强制性记录锁的文件进行读写
* 某些`ioctl`操作
* 某些进程间通信函数

注意：虽然读写磁盘文件会暂时阻塞调用者，但并不能将与磁盘I/O有关的系统调用视为`低速`

非阻塞I/O使我们可以发出`open`、`read`和`write`这样的I/O操作，并使这些操作不会永远阻塞。如果这种操作不能完成，则调用会立即出错返回。

对于一个给定搞得描述符，有两种方式指定其为非阻塞I/O：

1. 如果调用`open`函数获得描述符，则可指定`O_NONBLOCK`标志
2. 对于已经打开的一个描述符，则可调用`fcntl`，有该函数打开`O_NONBLOCK`文件状态标志

## 记录锁

在大多数UNIX系统中，当两个人同时编辑一个文件时，该文件的最后状态取决于该文件的最后一个进程。为了保证有些应用程序，如数据库，能够单独的写一个文件，UNIX系统提供了记录锁机制。

记录锁的功能是：当第一个进程正在读或修改文件的某个部分时，使用记录锁可以阻止其他进程修改同一文件区。

使用记录锁的方式有很多，下面一次讲解

### `fcntl`记录锁

```c
#include <fcntl.h>
int fcntl(int fd,int cmd,.../*strcut flock *flockptr */);
// 出错返回-1，成功见下文

struct flock {
    short l_type; // F_RDLCK,F_WRLCK,F_UNLCK
    short l_whence;// SEEK_SET,SEEK_CUR,SEEK_EDN
    off_t l_start; // offset int bytes;
    off_t l_len; // length,int bytes; 0 means lock to EOF
    pid_t l_pid; // return with F_GETLK
};
```

关于加锁好解锁区域的说明要注意以下几点：

* 指定区域起始偏移量的两个元素与`lseek`函数中的最后两个参数类似
* 锁可以在当前文件尾端处开始或者越过尾端开始，但是不能再文件起始位置之前开始
* 若`l_len`为`0`，则表示锁的范围可以扩展到最大可能偏移量。
* 为了对整个文件加锁，我们可以设置`l_start`和`l_whence`指向的起始位置，并指定长度`l_len`为`0`。
* 对于锁的类型有一个基本规则：任意多个进程在一个给定的字节上可以共有一把共享的读锁，但是在一个给定字节上只能有一个进程有一把独占写锁

要使用`fcntl`记录锁，`cmd`参数必须是一下三项中的一个：

* `F_GETLK`：判断由`flockptr`所描述的锁是否会被另一把锁排斥(阻塞)。如果不存在，会将`l_type`修改为`F_UNLCK`，其他信息不变。如果存在另一把锁，则会阻止创建指向的锁
* `F_SETLK`：设置有`flockptr`锁描述的锁。如果我们试图获取一把读锁或写锁，而兼容性规则阻止系统该给我们这把锁，那么`fcntl`会立即出错返回，并将`errno`设置为`EACCESS`或者`EAGAIN`。当`flockptr`中的锁的类型为`F_UNLCK`时，表示清除锁
* `F_SETLKW`：这是`F_SETLK`命令的阻塞版。如果区域提前被其他进程加了锁，那么该调用会休眠进程，直到创建的锁可用为止

锁的隐含继承和释放：

1. 锁与进程和文件两个相关联。
   1. 当一个进程终止时，它所建立的锁全部释放
   2. 无论一个描述符何时关闭，该进程通过这一描述符引用的文件上的任何一把锁都会释放
2. 有`fork`产生的子进程不继承父进程所设置的锁
3. 执行`exec`后，新程序可以继续原执行程序的锁。

建议性锁和强制性锁：

* 强制性锁：让内核检查每一个`open`、`read`和`write`，验证调用进程是否违背了正在访问的文件上的某一把锁。

## I/O多路转接

> 为了使用I/O多路转接技术，先构造一张我们感兴趣的描述符的列表，然后调用一个函数，直到这些描述符中的一个已准备好进行I/O时，该函数才返回。
>
> `poll`、`pselect`和`select`这三个函数使我们能够执行`I/O多路转接`。
>
> 在从这些函数返回时，进程会被告知那些描述符已经准备好可以进行I/O。

### 函数`select`和`pselect`

`select`的参数可以告诉内容一下信息：

* 我们关心的描述符
* 对于描述符我们所关心的条件
* 愿意等待多长时间
* 已经准备好的描述符的总数量
* 对于读、写或异常这三个条件中的每一个，那些描述符已经准备好。

```c
#include <sys/select.h>
int select(int maxfdp1,fd_set *restrict readfds,
          fd_set *restrict writeds, fd_set *restrict execptfds,
          struct timeval *restrict tvptr);
// 准备就绪的描述符数目，超时返回0，出错返回-1
```

* 最后一个参数标志愿意等待的时间长度，单位为秒和微妙。有三种情况
  * `tvptr == NULL`。表示永远等待。如果捕捉到一个信号则中断等待。当指定描述符中的一个已经准备好或捕捉到一个信号则返回
  * `tvptr->tv_sec == 0 && tvptr->tv_usec == 0`。根本不等待。测试所有指定的描述符并立即返回。
  * `tvptr->tv_sec ！= 0 && tvptr->tv_usec ！= 0`。等待指定描述和微妙数
* 中间三个参数`readfds`、`writefds`和`execptfds`是值想描述符集的指针

有四个函数来操作`fd_set`结构：

```c
#include <sys/select.h>
int FD_ISSET(int fd,fd_set *fdset);
// 如果fd在fdset中，则返回非0，不在返回0
void FD_CLR(int fd,fd_set *fdset);
void FD_SET(int fd,fd_SET *fdset);
void FD_ZERO(fd_set* fdset);
```

* 中间三个参数的任意一个或全部都可以是空指针，表示对相应的条件不关心
* `select`第一个参数`maxfdp1`的意思是最大文件描述符编号值加1。
* 返回值表示准备好的描述符，其含义如下：
  * 若对读集中的一个描述符进行`read`操作不会阻塞，则是准备好的
  * 若对写集中的一个描述符进行`write`操作不会阻塞，则是准备好的
  * 如果对异常条件集中的一个描述符有一个未决异常条件，则是准备好的
  * 对于读、写和异常条件，普通文件描述符总是返回准备好

```c
#include <sys/select.h>
int select(int maxfdp1,fd_set *restrict readfds,
          fd_set *restrict writeds, fd_set *restrict execptfds,
          const struct timespec *restrict tsptr,
          const sigset_t *restrict sigmask);
// 准备就绪的描述符数目，超时返回0，出错返回-1
```

除了下列节点，`select`和`pselect`相同：

* 时间参数的结构不同
* 参数的`const`属性
* 多了最后一个参数，用来设置信号屏蔽字

### 函数`poll`

`poll`函数类似于`select`函数，但是`poll`函数可用于任何类型的文件描述符

```c
#include <poll.h>
int poll(struct pollfd fdarray[],nfds_t nfds,int timeout);
// 返回准备就绪的描述符数目，超时返回0，出错返回-1

struct pollfd {
    int fd;
    short events;
    short revents;
};
```

* `fdarray`数组中的元素数有`nfds`指定
* 最后一个参数表示我们愿意等待的时间
  * `timeout == -1`。永久等待
  * `timeout == 0`。不等待
  * `timeout > 0`。等待指定**毫秒**数

## POSIX异步I/O

> `POSIX异步接口`为对不同类型的文件进行异步I/O提供了一套一致的方法。
>
> 这些异步I/O接口使用`AIO控制块`来描述I/O操作。结构如下
>
> ```c
> struct aiocb {
>     int aio_fildes;  // 被打开的文件描述符
>     off_t aio_offset;  // 操作的起始偏移量。如果使用(O_APPEND)模式打开，则该字段失效
>     volatile void *aio_buf;  // 缓冲器开始地址
>     size_t aio_nbytes;  // 操作的字节数
>     int aio_reqprio;  // 为异步I/O请求提示顺序
>     struct sigevent aio_sigevent;  // 结构如下
>     int aio_lio_opcode;  // 只能基于列表的异步I/O
> };
> 
> struct sigevent {
>     int sigev_notify;  // 通知类型(SIGEV_NONE,SIGEV_SIGNAL,SIGEV_THREAD)
>     int sigev_signo;  // 信号编号
>     union sigval sigev_value;  // 同时参数
>     void (*sigev_notify_function)(union sigval);  // 通知处理函数
>     pthread_attr_t *sigev_notify_attributes;  // 通知属性
> };
> ```

可以调用下面两个函数来进行异步读写操作

```c
#include <aio.h>
int aio_read(struct aiocb *aiocb);
int aio_write(struct aiocb *aiocb);
// 成功返回0，出错返回-1
```

强制所有等待中的异步操作不等待而写入持久化的存储中，可以设立一个`AIO控制块`并调用下面这个函数

```c
#include <aio.h>
int aio_fsync(int op,struct aiocb *aiocb);
// 成功返回0，出错返回-1
```

* op参数有以下可选项
  * `O_DSYNC`,相当于调用了`fdatasync`
  * `O_SYNC`,相当于调用了`fsync`

获取异步I/O操作的完成状态的函数

```c
#include <aio.h>
int aio_error(const struct aiocb *aiocb);
```

* 该函数的返回值有下面四中情况：
  * 0。异步操作成功完成。需要调用下一个函数来获取操作返回的值
  * -1。调用失败，`errno`记录错误值
  * `EINPROGRESS`。等待状态

上面的函数成功后，可以使用下面这个函数获取异步操作的返回值

```c
#include <aio.h>
ssize_t aio_return(const struct aiocb *aiocb);
```

* 异步操作未完成时调用该函数，其返回的结构是未定义的
* 一点调用了该函数，操作系统就可以释放掉包含了I/O操作返回值的记录
* 如果函数本身失败，会返回-1，并设置`errno`

使用下面的函数来阻塞进程，等待异步操作完成

```c
#include <aio.h>
int aio_suspend(const struct aiocb *const list[],int nent,const struct timespec *timeout);
// 成功返回0，出错返回-1
```

* list是指向一个`AIO控制块数组`的指针。
* `nent`表明了数组中的条目数。
* 数组中的空指针会被跳过，其他指针必须指向已初始化的`AIO控制块`

取消异步I/O操作的函数

```c
#include <aio.h>
int aio_cancel(int fd,struct aiocb *aiocb);
```

* 如果`aiocb`为`NULL`，系统将会尝试将所有的`fd`上未完成的异步I/O操作取消掉
* 返回值如下：
  * `AIO_ALLDONE`，所有操作在尝试取消它们之前已经完成
  * `AIO_CANCELED`，所有要求的操作都已经取消
  * `AIO_NOTCANCELED`，至少有一个要求的操作没有被取消
  * `-1`，调用失败，`errno`中存放错误码

下面这个函数提交一系列由一个`AIO控制块列表`描述的I/O请求

```c
#include <aio.h>
int lio_listio(int mode,struct aiocb *restrict const list[restrict],int nent,
              struct sigevent *restrict sigev);
// 成功返回0，出错返回-1
```

* `mode`，决定了I/O是否真的是异步的
  * `LIO_WAIT`，该函数将在所有由列表指定的I/O操作完成后返回。`sigev`将被忽略
  * `LIO_NOWAIT`，该函数将在I/O请求入队后立即返回。所有操作完成后，按照`sigev`指定的，被异步地通知

## 散布读和聚集写函数

> 这两个函数用于在一次函数调用中读、写多个非连续缓冲区。

```c
#include <sys/uio.h>
ssize_t readv(int fd,const struct iovec *iov,int iovcnt);
ssize_t writev(int fd,const struct iovec *iov,int iovcnt);
// 返回已读或已写的字节数，出错返回-1

struct iovec {
    void *iov_base;
    size_t iov_len;
}
```

## 函数`readn`和`writen`

> 管道、FIFO已经某些设备有两种性质：
>
> 1. 一次read操作返回的值可能少于要求的数据，即使没有达到文件尾端也可能会这样。这不是错误
> 2. 一次write操作返回的值可能少于要求的数据，这也不是一个错误。
>
> 对于处理普通文件时使不需要考虑上面这两种情况的。

函数是由`《APUE》`实现，代码可网上查询，或进入[GitHub](https://github.com/cxldada/unix_test/tree/master/include/rdn.c)查看

## 存储映射I/O

> 将一个磁盘文件映射到存储空间中的一个缓冲区上，于是，当从缓冲区读写数据时，就相当于在文件中进行读写操作

在使用这种功能之前，应首先告诉内核讲一个给定的文件映射到一个存储区中。这由下面这个函数实现

```c
#include <sys/mman.h>
void *mmap(void *addr,size_t len,int prot,int flag,int fd,off_t off);
// 成功返回映射区的起始地址，出错返回MAP_FAILED
```

* `addr`参数用于指定映射存储区的起始地址。通常设为0，表示由系统选择映射区的起始地址。
* `fd`指定要被映射文件的描述符
* `off`是要映射字节在文件中的起始偏移量
* `prot`指定了映射存储区的保护要求
  * `PROT_READ`映射可读
  * `PROT_WRITE`映射可写
  * `PROT_EXEC`映射可执行
  * `PROT_NONE`映射不可访问
  * 上述参数可以按位或(除了不可访问标志位外)
* 映射存储区位于堆和栈之间。这属于实现细节，各种实现之间可能不同
* `flag`参数影响映射存储区的多种属性
  * `MAP_FIXED`返回值必须等于`addr`参数指向的地址。不利于可移植性，不鼓励使用
  * `MAP_SHARED`，该标志描述了本进程对映射区所进行的存储操作的配置。表示存储操作相当于对源文件进行操作
  * `MAP_PRIVATE`，该标志说明，对映射区的操作导致创建该映射文件的一个私有副本。只影响副本不影响源文件

更改现有映射的权限

```c
#include <sys/mman.h>
int mprotect(void *addr,size_t len,int prot);
// 成功返回0，出错返回-1
```

* `prot`参数与`mmap`函数中的参数一致
* `addr`必须是系统页长的整数倍

重写共享映射区(`MAP_SHARED`)的内容到文件中

```c
#include <sys/mman.h>
int msync(void *addr,size_t len,int flags);
// 成功返回0，出错返回-1
```

* 如果映射区是私有的，那么不修改该映射文件。
* `addr`必须是系统页长的整数倍
* `flags`参数控制冲洗存储区的程度
  * `MS_ASYNC`，简单的调试要写的页。必填(2选1)
  * `MS_SYNC`，等待写操作完成。必填(2选1)
  * `MS_INVALIDATE`，通知操作系统丢弃那些与底层存储器没有同步的页。可选

解除映射区的函数

```c
#include <sys/mman.h>
int munmap(void *addr,size_t len);
// 成功返回0，出错返回-1
```

* 该函数并不影响映射的对象。也就是说，调用该函数的时候并不会使映射区的内容写到磁盘文件上
* 解除映射后，`MAP_PRIVATE`存储区的修改会被丢弃，`MAP_SHARED`会在写入数据后的某个时刻自动同步到磁盘文件上