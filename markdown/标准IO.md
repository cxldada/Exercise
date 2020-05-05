# 标准IO库

标准IO库是一个方便用户使用的库，他让用户不用关心缓冲区、块长度等问题。但是我们还是认真学习标准IO库，因为如果不深入了解标准IO库的某些特点，那么在使用的时候可能会带来一些小麻烦。

另外，标准IO库最炫酷的地方就是自从[dmr](https://zh.wikipedia.org/wiki/%E4%B8%B9%E5%B0%BC%E6%96%AF%C2%B7%E9%87%8C%E5%A5%87)把它创作出来,一直到后面的35年里几乎没有对标准IO库进行过改动。我只能说牛逼啊！

## 流和FILE对象

在之前学习文件IO的时候，可以看得出来所有的IO函数都是以打开的文件描述符为基础来进行操作的。而标准IO库则是围绕着流来进行相关IO操作的。

由于有多种字符集(ASCII、国际字符集等)，每种字符集的字节宽度也是不一样的，有的一个字符占一个字节（单字节），有的一个字符占多个字节（宽字节）。标准IO库为了满足各种字符集，所以流是可以设置单字节或宽字节的。

### 流的定向

设置流是单字节还是宽字节这个动作也叫设置流的定向。当一个流刚刚创建的时候，是没有定向的。若后续的第一个IO操作是一个用于处理单字节的IO函数，那么流会自动的设置为单字节，同理，如果是一个处理多字节IO函数的话，那么流就被定向为宽字节。

#### 相关函数

能够更改流定向的函数只有两个：

* `freopen`函数
* `fwide`函数

先看`fwide`函数，`freopen`函数在后面讲

```c
#include <stdio.h>
#include <wchar.h>
int fwide(FILE *fp,int mode);
// 如果流是宽定向，则返回正值；如果流是字节定向，则返回负值；若流未定向则返回0
```

#### 参数解释

mode参数的不同值控制着`fwide`函数的不同工作

* 如果mode为负值，则将流设置为字符定向
* 如果mode为正值，则将流设置为宽定向
* 如果mode为0，则返回当前流的状态，并不改变流的定向

#### 注意事项

* `fwide`无法改变已定向的流
* 这个函数是没有出错返回的。
* 由于没有出错返回，所有一般在使用这个函数前现将`errno`设置为0，然后在调用后来检测`errno`的值

### FILE对象

当我们去打开一个流的时候，会得到一个FILE对象，它是一个结构体，里面包含了标准IO库为管理流需要的所有信息，里面包含了用于实际IO操作的文件描述符，指向缓冲区的指针，缓冲区的大小，缓冲区当前字符数和出错标志等等。

### 标准输入、标准输出和标出错误

在学习文件IO的时候应该还记的这三个文件描述符吧，他们是一个进程一启动就会拥有的三个打开的文件描述符，他们可以用`STDIN_FILENO`，`STDOUT_FILENO`，`STDERR_FILENO`来引用

而标准也定义了相应的三个文件流来使用，他们分别是`stdin`,`stdout`,`stderr`。这三个文件指针定义在`<stdio.h>`中

## 缓冲

### 缓冲简介

> 缓冲的目的：为了更少的调用系统IO。在学习文件IO的时候提到过，不同缓冲长度对执行系统IO是有影响的
>
> 标准IO库中的流会对缓冲进行自动化的管理，不需要用户关心
>
> 标准IO库提供了三种类型的缓冲：
>
> 1. 全缓冲。这种情况下，只有当缓冲的被填满使才会执行一次实际的IO操作。标准IO库一般使用`malloc`函数来获取需要的缓冲区空间
> 2. 行缓冲。这种情况是，只有当遇到换行符时就会执行一次实际的IO操作，行缓冲有两个限制：
>    1. 如果缓冲区被填满了还没有遇到换行符的话，也是会执行一次实际IO操作的，应为缓冲区的大小是有限的嘛。
>    2. 任何时候只要标准IO库要求从一个不带缓冲的流或者一个行缓冲的流中得到输入数据的时候，都会冲洗所有的行缓冲输出流。
> 3. 不带缓冲。这种情况下标准IO库是不会对字符进行缓冲存储的。这种一般用于需要快速显示信息的地方，比如说标准错误，因为需要及时的显示错误信息。
>
> 上面行缓冲中提到了冲洗，这里解释一下：标准IO库的冲洗表示将缓冲区存储的字符存入磁盘，并清空缓冲区。
>
> 在后面的学习中还有一个冲洗的概念，它表示放弃存储在缓冲区中的数据。

### 更改流的缓冲类型的函数

```c
#include <stdio.h>
void setbuf(FILE *restrict fp,char *restrict buf);
int setvbuf(FILE *restrict fp,char *restrict buf,int mode,size_t size);
// 成功返回0，出错为非0
```

**这两个函数要在一个已经打开的流上使用**

### 参数说明

`setbuf`函数的相关参数说明：

* `buf`如果为`NULL`，则设置为不带缓冲
* `buf`是一个指向长度为`BUFSIZ`（`<stdio.h>`中）的缓冲区，通常会设置为全缓冲，但是如果该流与一个终端设备相关，则某些系统可能设置为行缓冲

`setvbuf`函数的相关参数说明：

* mode参数决定了要设置的类型
  * `_IOFBF`：全缓冲，必须有`buf`和`size`参数，指定缓冲地址和缓冲大小
  * `_IOLBF`：行缓冲
  * `_IONBF`：不带缓冲，忽略`buf`和`size`参数
* 如果流带缓冲，而`buf`为`NULL`，则标准IO库会自动为缓冲区设置适当的长度

### 强制冲洗流的函数

```c
#include <stdio.h>
int fflush(FILE *fp);
// 成功返回0，出错返回EOF
```

这个函数的作用是将该流中所有未写的数据传入内核。

有一种特殊情况，如果`fp`参数为`NULL`的话，则冲洗所有的输出流。

## 打开和关闭流

### 打开流的函数

```c
#include <stdio.h>
FILE *fopen(const char *restrict pathname,const char *restrict type);
FILE *freopen(const char *restrict pathname,const char *restrict type,FILE *restrict fp);
FILE *fdopen(int fd,const char *type);
// 成功返回文件指针，出错返回NULL
```

这三个函数的区别：

* `open`函数打开路径名为pathname的一个指定的文件
* `freopen`函数在一个指定的流上打开一个文件，如果该流已经打开，则先关闭，若流已定向，则清楚清除该定向
* `fdopen`函数取一个已有的文件描述符，使一个标准IO库流与该描述符结合

### 参数说明

type参数指定了IO流的读写方式：

|     type     |          说明           |         对应的open标志          |
| :----------: | :---------------------: | :-----------------------------: |
|    r或rb     |         读打开          |           `O_RDONLY`            |
|    w或wb     | 把文件截断为0，为写创建 |  `O_WRONL | O_CREAT | O_TRUNC`  |
|    a或ab     | 在文件尾打开，为写创建  | `O_WRONLY | O_CREAT | O_APPEND` |
| r+或r+b或rb+ |        读写打开         |            `O_RDWR`             |
| w+或w+b或wb+ |  文件截断为0，读写打开  |  `O_RDWR | O_CREAT | O_TRUNC`   |
| a+或a+b或ab+ |   文件尾读写，或创建    |  `O_RDWR | O_CREAT | O_APPEND`  |

字符b作为type的一部分是用来区分文本文件和二进制文件的，但是对`unix`内核而言，并不区分这两种文件，所有并没有什么卵用

对于`fdopen`函数而言，type参数稍微有点不同：

* `fdopen`为写而打开并不会截断文件，因为文件描述符已打开，所有由open函数的`O_TRUNC`来指定
* 标准IO追加写方式也不能用于创建该文件。这很容易想到，都拿到文件描述符了，说明文件已经存在了，还创建个毛

当以读写方式打开一个文件的时候，有以下限制

* 如果中间没有`fflush`、`fseek`、`fsetpos`或者`rewind`，则输出的后面不能直接跟输入
* 如果中间没有`fseek`、`fsetpos`或者`rewind`，或者一个输入操作没有达到文件尾端，则在输入操作后不能直接跟随输出

还有一点需要注意：

* 在时候w或者a的时候，如果创建了新的文件，我们是无法控制该文件的访问权限位的

### 关闭一个打开的流

```c
#include <stdio.h>
int fclose(FILE *fp);
// 成功返回0，出错返回EOF
```

## 处理单个字符读写流的函数

### 从一个流中读取字符的函数

```c
#include <stdio.h>
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);
// 成功返回下一个字符，若已达到文件尾或者出错，则返回EOF
```

注意事项：

* `getc`和`fgetc`的差别
  * `getc`是宏定义
  * `fgetc`是一个函数实现的，所以可以将`fgetc`的地址作为参数传递给另一个函数
  * 调用`getc`比调用`fgetc`要快，因为调用函数比调用宏的时间长
* `getchar` == `getc(stdin);`

返回值为整数的原因：

*   这样可以返回所有可能的字符值再加上一个已出错或已达文件尾端的指示值

### 流状态判断函数

大多数实现中，都会为每个流维护两个标志：

*   出错标志
*   文件结束标志

从上面的三个读取函数的返回可以看出，我们无法判断流是出错了还是达到文件尾了，所以有了下面三个函数

```c
#include <stdio.h>
int ferror(FILE *fp);
int feof(FILE *fp);
// 如果条件为真返回非0，为假返回0
void clearerr(FILE *fp);
// 清除出错标志和文件结束符标志
```

### 将取出的值压会缓冲区的函数

如果使用上面三个读取字符的函数取出了字符，可以使用下面这个函数把它压会缓冲区

```c
#include <stdio.h>
int ungetc(int c,FILE *fp);
// 成功返回c，出错返回EOF
```

这个压会和栈的原理一样，先进后出。ISO C标准允许实现支持任何次数的回送，但是只能一次回送一个字符。

**注意不能会送`EOF`。如果已经达到文件尾端仍然可以成功回送，因为`ungetc`函数成功调用后会清除掉该流的文件结束符标志**

**回送字符时，其实是写回标准I/O库的流缓冲区中，而不是底层文件或设备上**

### 输出函数

```c
#include <stdio.h>
int putc(int c,FILE *fp);
int fputc(int c,FILE *fp);
int putchar(int c);
// 成功返回c，出错返回EOF。
// 这三个函数对应上面三个读的函数，性质也基本相同
```

## 以行为单位读写流的函数

### 读取函数

```c
#include <stdio.h>
char *fgets(char *restrict buf,int n,FILE *restrict fp);
char *gets(char *buf);
// 成功返回buf，若达到文件尾或者出错，则返回NULL
```

注意事项：

* `fgets`函数可以指定缓冲区的长度，当填满缓冲区时还没有遇到换行符则不会继续读，如果遇到换行符缓冲区还未满时也不会继续读了
* `fgets`读取的最大数量是`n-1`，因为最后一个字符需要以`null`来填充，用来表示结尾
* 不推荐是用`gets`函数，原因有两个：
  * 不能指定缓冲区长度，容易造成缓冲区溢出
  * `gets`函数不将换行符写入缓冲区

### 写入函数

```c
#include <stdio.h>
int fputs(const char *restrict str,FILE *restrict fp);
int puts(cosnt char *str);
// 成功返回非负值，出错返回EOF
```

注意事项：

* 两个函数都是将一个以`null`字节终止的字符串写入指定流
* `puts`函数还会在后面自动的加一个换行符，而`fputs`不会
* 也不推荐使用`puts`函数，虽然它还算安全，但是容易忘记后面自动加的换行符

## 二进制IO函数

> 二进制IO主要用以一次读写一个结构的数据，因为`getc`、`putc`和`fgets`、`fputs`这几个函数他们都是在遇到结束符或换行符的时候终止读写。想象一下如果一个结构读到一半终止了会是多么的麻烦，所有提供了下面两个二进制IO函数

```
#include <stdio.h>
size_t fread(void *restrict ptr,size_t size,size_t nobj,FILE *restrict fp);
size_t fwrite(void *restrict ptr,size_t size,size_t nobj,FILE *restrict fp);
// 两个函数都返回读写对象的数量
```

### 参数说明

* `ptr`是指向存放结构体的指针
* `size`是单个结构的大小
* `nobj`是需要读取几个结构体
* `fp`就是IO流

这两个函数达到文件尾端或出错，返回的值会小于需要`nobj`，这个时候还是要调用`ferror`或`feof`的函数来判断到底是哪种情况

二进制IO只能用于读在同一系统上已写的数据，原因是：

1. 在一个结构中，同一成员的偏移量可能随编译程序和系统的不同而不同(由于不同的对齐要求)。
2. 用来存储多字节整数和浮点值的二进制格式在不同搞得系统结构间也可能不同

## 定位流

在UNIX环境中共有三种方式来定位流：

1. `ftell`和`fseek`函数。他们是最早用来定位流的函数，但是它们都假定文件的位置可以存放在一个长整型中
2. `ftello`和`fseeko`函数。这是单一UNIX协议引入的两个函数。他们使用off_t代替了长整型
3. `fgetpos`和`fsetpos`函数。这是ISO C引入的。他们使用一个抽象数据类型`fpos_t`记录文件的位置。这种数据可以根据需要定义一个足够大的数。

**如果需要将程序移植到非UNIX系统上运行的话，最好使用`fgetpos`和`fsetpos`函数。**

下面一个一个的讲解

```c
#include <stdio.h>
long ftell(FILE *fp);
// 成功返回当文件文件位置，出错返回 -1L

int fseek(FILE *fp,long offset,int whence);
// 成功返回0，出错返回-1

void rewind(FILE *fp);
// 将流设置到文件的起始位置
```

### 注意事项

- `whence`参数与`lseek`函数相同可以取：`SEEK_SET、SEEK_CUR、SEEK_END`
- 对于一个文本文件来说，如果是用`fseek`的话，`whence`必须是`SEEK_SET`，而且`offset`只能是`0`或`ftell`所返回的值。对于二进制文件就没有这种限制

下面两个函数是`Single UNIX Specification`引入的，使文件偏移量不一定是长整型，他们使用了off_t代替了长整型

```c
#include <stdio.h>
off_t ftello(FILE *fp);
// 成功返回当文件文件位置，出错返回(off_t)-1

int fseeko(FILE *fp,off_t offset,int whence);
// 成功返回0，出错返回-1

// 下面这两个函数是ISO C提供的。如果想要移植到非unix系统中，最好使用它们
int fgetpos(FILE *restrict fp,fpos_t *restrict pos);
int fsetpos(FILE *fp,const fpos_t *pos);
// 成功返回0，出错返回非0
```

## 格式化IO -- 输出

```c
#include <stdio.h>
int printf(const char *restrict format,...);
int fprintf(FILE *restrict fp,const char *restrict format,...);
int dprintf(int fd,const char *restrict format,...);
// 成功返回输出的字符数，出错返回负值

int sprintf(char *restrict buf,const char *restrict format,...);
// 返回要存入数组的字符数，若编码出错则返回负值

int snprintf(char *restrict buf,size_t n,const char *restrict format,...);
// 若缓冲区足够大，返回要存入数组的字符数，若编码出错则返回负值
```

### 注意事项

* printf将格式化数据写到标准输出
* fprintf写到指定的文件流
* dprintf写到指定的文件描述符
* sprintf和snprintf写到字符数组中。snprintf会在数组尾部自动加入一个null字节，但是返回的数值不计算该字符
* sprintf是不安全的，因为它有可能会导致缓冲区溢出，它无法设置写入的大小，而snprintf就相对安全

### 参数说明

其他参数不做具体说明，因为一看就懂，重点说明一下format参数。

format格式如下

​	` %[flags][fldwidth][precision][lenmodifier]convtype`

#### flags标志

|  标志  |                             说明                             |
| :----: | :----------------------------------------------------------: |
|   '    |                     将整数按千位分组字符                     |
|   -    |                       字段内左对齐输出                       |
|   +    |                  总是显示带符号转换的正负号                  |
| (空格) |       如果第一个字符不是正负号，则在其前面加上一个空格       |
|   #    | 指定另一种转换格式(例如十六进制，加`0x`前缀)。如果不指定这个参数显示十六进制或者八进制，都是没有前缀的 |
|   0    |                 添加前导0(而非空格)进行填充                  |

#### `fldwidth`标志

最小的字段宽度，多余的字符位置用空格填充(也可以是0填充，看flags标志),是一个的非负十进制数或星号(*)

#### `precision`标志

说明整型转换后最少输出数字位数、浮点数转换后小数点后的最少位数、字符转换后最大字节数。精度是一个点(.)，后面跟随一个可选的非负十进制数或星号(*)

#### `lenmodifier`标志

用来说明参数长度的，不常用，具体请上网查询

#### `convtype`标志

上面的几个标志都是可选项，但是这个标志是必选项，它用来控制如何解释参数

| 转换类型 |                说明                 |
| :------: | :---------------------------------: |
|   d、i   |            有符号十进制             |
|    o     |            无符号八进制             |
|    u     |            无符号十进制             |
|   x、X   |           无符号十六进制            |
|   f、F   |            双精度浮点数             |
|   e、E   |        指数格式双精度浮点数         |
|   g、G   |    根据转换后的值解释f、F、e、E     |
|   a、A   |    十六进制指数格式双精度浮点数     |
|    c     | 字符（若带长度修饰符l，表示宽字符） |
|    s     |               字符串                |
|    p     |           指向void的指针            |
|    n     |  到目前为止函数已输出的字符的数目   |
|    %     |              一个%字符              |
|    C     |             宽字符 = lc             |
|    S     |            宽字符串 = ls            |

### 类似函数

还有5个函数是`printf`族的变体，只是可变参数(...)替换成了`arg`

```c
#include <stdarg.h>
#include <stdio.h>

int vprintf(const char *restrict format,va_list arg);
int vfprinrf(FILE *restrict fp,const char *restrict format,va_list arg);
int vdprinrf(int fd,const char *restrict format,va_list arg);
// 成功返回输出的字符数，出错返回负值

int vsprintf(char *restrict buf,const char *restrict format,va_list arg);
// 成功返回存入数组的字符数，编码出错返回负值

int vsnprintf(char *restrict buf,size_t n,const char *restrict format,va_list arg);
// 若缓冲区足够大，返回存入数组的字符数，编码出错则返回负值
```



## 格式化IO -- 输入

```c
#include <stdio.h>
int scanf(const char *restrict format,...);
int fscanf(FILE *restrict fp,const char *restrict format,...);
int sscanf(const char *restrict buf,const char *restrict format,...);
// 成功返回赋值的输入项数，出错或在任一转换前已达到文件尾端，则返回EOF

三个同族函数
#include <stdarg.h>
int vscanf(const char *restrict format,va_list arg);
int vfscanf(FILE *restrict fp,const char *restrict format,va_list arg);
int vsscanf(const char *restrict buf,const char *restrict format,va_list arg);
```

这六个函数的format格式与输出是基本相同的

## 实现细节

所有的标准库IO最后都会调用之前我们学过得系统IO。每个标准IO流都对应一个文件描述符。可以使用下面的这个函数来获得

```c
#include <stdio.h>
int fileno(FILE *fp);
// 返回与流相关联的文件描述符
```

拿到了文件描述符就可以使用系统IO做进一步处理，比如`dup`或`fcntl`等等

## 临时文件

标准IO库中提供了两个函数用于创建临时文件

```c
#include <stdio.h>
char *tmpnam(char *ptr);
// 指向唯一路径名的指针

FILE *tmpfile(void);
// 返回文件指针，出错返回NULL
```

* `tmpnam`函数所产生的路径名存放在一个静态区中。如果后续连续调用`tmpnam`的话会重写该静态区，如果想要保存上次的临时文件，我们就保存指针的指向的内容，而直接使用该指针。
* 如果`ptr`参数不是`NULL`的话，则`ptr`的字符长度至少是`L_tmpnam`。该常量定义在头文件`<stdio.h>`中
* `tmpfile`创建一个临时二进制文件(打开方式是`wb+`)，在关闭该文件或程序时会自动删除该文件

### 同族函数

```c
#include <stdlib.h>
char mkdtemp(char *template);
// 成功返回指向目录名的指针，出错返回NULL

int mkstemp(char *template);
//成功返回文件描述符，出错返回-1
```

* `mkdtemp`用于创建临时目录。`mkstemp`用于创建临时文件
* `template`参数的是一个路径名，但是该路径名的后6位必须是`XXXXXX`
* `mkdtemp`创建的临时目录的权限位：`S_IRUSR | S_IWUSR | S_IXUSR`。除此之外还可以使用文件模式创建屏蔽字进一步限制
* `mkstemp`创建的临时文件与`tmpfile`创建的临时文件不同，它不会被自动删除。如果需要，必须手动删除
* `template`参数最好是定义成字符数组。如果是数组的话，该数组的空间是分配在栈上的，所以`mkstemp`函数可以进行读写操作，如果使用字符指针的话，只有指针变量是在栈上，而实际指向的内容存在可执行文件的只读段中，所以`mkstemp`不能够修改会导致程序崩溃异常

**注意：**

使用`tmpnam`和`tmpfile`至少有一个缺点：在返回唯一的路径名和用该名字创建文件之间存在一个时间窗口，在这个时间窗口中，另一个进程可以用相同的名字创建文件。

## 内存流

内存流相较于普通的文件流主要是在于普通文件流有底层文件，而内存流没有。普通的文件流需要将缓冲区的内容写到磁盘中，而内存流则是缓冲区与主存之间的数据交流。

```c
#include <stdio.h>
FILE *fmemopen(void *restrict buf,size_t size,const char *restrict type);
// 成功返回流指针，出错返回NULL
```

* 只有最后一个参数需要说明一下，它与`fopen`中的`type`是相同的，所以可以参数上面`fopen`函数的解释来使用
* 虽然type的取值相同，但是功能细节还是有点小差别的，具体如下：
  * 如果以追写的方式打开内存流，当前文件位置设为缓冲的第一个null字节。如果缓冲区中不存在`null`字节，则当前位置设置为缓冲区结尾的后一个字节。不是追写方式打开的话，则当前位置设置为缓冲的开始位置。因为追写模式通过第一个null字节来确定数据的尾端
  * 如果`buf`参数为`nul`l指针，则对打开的流进行读写操作是没有任何意义的
  * 任何时候需要增加流缓冲区中的数据量，以及调用`fclose、fflush、fseek、fseeko`以及`fsetpos`时都会在当前位置写入一个`null`字节

### 同族函数

```c
#include <stdio.h>
FILE *open_memstream(char **bufp,size_t *sizep);
#include <wchar.h>
FILE *open_wmemstream(wchar_t **bufp,size_t *sizep);
// 成功返回流指针，出错返回NULL
```