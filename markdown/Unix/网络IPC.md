#  网络IPC

## 套接字描述符

> 套接字是通信端点的抽象。就像访问文件需要使用文件描述符一样。应用访问套接字也需要使用描述符。而且很多用于处理文件描述符的函数，也可以对套接字描述符使用

### 创建套接字描述符的函数

```c
#include <sys/socket.h>
int socket(int domain,int type,mint protocol);
// 成功返回套接字描述符，出错返回-1
```

* `domain`参数确定通信通信的特性，包括地址格式。取值如下：
  * `AF_INET`：IPv4协议
  * `AF_INET6`：IPv6协议
  * `AF_UNIX`：UNIX域
  * `AF_UPSPEC`：未指定
* `type`参数确定套接字的类型，进一步确定通信特征。取值如下：
  * `SOCK_DGRAM`：固定长度的、无连接的、不可靠的报文传递
  * `SOCK_RAW`：IP协议的数据报接口
  * `SOCK_SEQPACKET`：固定长度的、有序的、可靠的、面向连接的报文传递
  * `SOCK_STREAM`：有序的、可靠的、双向的、面向连接的字节流
* `protocol`参数通常为0，表示为给定的域和套接字类型选择默认协议。可用的协议有：
  * `IPPROTO_IP`：IPv4网络协议
  * `IPPROTO_IPV6`：IPv6网络协议
  * `IPPROTO_ICMP`：因特网控制报文协议
  * `IPPROTO_RAW`：原始IP数据包协议
  * `IPPROTO_TCP`：传输控制协议
  * `IPPROTO_UDP`：用户数据报协议
* 套接字描述符本质上是一个文件描述符，但是不是所有参数为文件描述符的函数都可以接受套接字描述符的。下面是函数整理：
  * `close`函数，可以释放套接字
  * `dup`和`dup2`函数，和一般文件描述符一样复制
  * `fchdir`，失败返回，并将`errno`设置为`ENOTDIR`
  * `fchomod`，行为未指定
  * `fchown`，有具体实现决定
  * `fcntl`，支持以下命令大部分命令
  * `fdatasync`和`fsync`，由具体实现定义
  * `fstat`，支持一些`stat`结构成员，但如何支持由具体实现定义
  * `ftruncate`，未指定
  * `ioctl`，支持部分命令，依赖于底层设备驱动
  * `lseek`，由实现定义(通常是失败返回，并将`errno`设置为`ESPIPE`)
  * `poll`，正常工作
  * `select`，正常工作

### 禁止一个套接字I/O

```c
#include <sys/socket.h>
int shutdown(int sockfd,int how);
// 成功返回0，出错返回-1
```

* `how`取值如下：
  * `SHUT_RD`：关闭读端。之后就无法从套接字中读取数据
  * `SHUT_WR`：关闭写端。之后就无法向套接字中发送数据
  * `SHUT_RDWR`：读写端全部关闭
* 可以使用`close`函数来关闭一个套接字，为什么还要多一个`shutdown`函数。理由如下：
  * 只有最后一个活动引用关闭时，`close`才会释放网络端点。比如复制一个套接字描述符后的情况。
  * `shutdown`可以很方便的不安比套接字双向传输中的一个方向

## 寻址

> 进程标识由两部分组成：计算机的网络地址和端口号

### 字节序

> 字节序是一个处理器架构特性，用于指示像整型这样的大数据类型内部的字节如何排序。
> 
> 在同一台计算机上的进程使用套接字通信时，一般不需要考虑字节序。

处理字节序的4个函数：

```c
#include <arpa/inet.h>
uint32_t htonl(uint32_t hostint32);
// 返回以网络字节序表示的32位整数
uint16_t htons(uint16_t hostint16);
// 返回以网络字节序表示的16位整数
uint32_t ntohl(uint32_t netint32);
// 返回以主机字节序表示的32位整数
uint16_t ntohs(uint16_t netint16);
// 返回以主机字节序表示的16位整数
```

* 这四个函数是有规律的：h表示主机，n表示网络，l表示长整型，s表示整型

### 地址格式

> 一个地址标识一个特定通信域的套接字端点，地址格式与这个特定的通信域相关。
> 
> 为使不同格式地址能够传入到套接字函数，地址会被强制装换成一个通用的地址结构`sockaddr`

```c
struct sockaddr {
    sa_family_t sa_family;
    char sa_data[];
    // ...
};
```

* 套接字实现可以自由的添加额外的成员并且定义`sa_data`的大小。

因特网地址定义在`<netinet/in.h>`中。结构如下：

```c
// IPv4因特网域中使用的结构(AF_INET)
struct in_addr {
    in_addr_t s_addr;
};

struct sockaddr_in {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr
};

// IPv6中使用的结构(AF_INET6)
struct in6_addr {
    uint8_t s6_addr[16];
};

struct sockaddr_in6 {
    sa_family_t sin6_family;
    in_port_t sin6_port;
    uint32_t sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t sin6_scope_id;
};
```

将地址转换成易读形式的函数

```c
#include <arpa/inet.h>
const char *inet_ntop(int domain,const void *restrict addr,char *restrict str,socklen_t size);
// 成功返回地址字符串指针，出错返回NULL
int inet_pton(int domain,const char *restrict str,void *restrict addr);
// 成功返回1，格式无效返回0，出错返回-1
```

* 在第二个函数中，`domain`参数只有两个值：`AF_INET`，`AF_INET6`。

### 地址查询

获取给定计算结系统的主机信息

```c
#include <netdb.h>
struct hostent *gethostent(void);
// 成功返回指针，出错返回NULL

void sethostent(int stayopen);
void endhostent(void);

struct hostent {	// 静态的
    char *h_name;
    char **h_aliases;
    int h_addrtype;
    int h_length;
    char **h_addr_list;
    // ...
};
```

* 如果主机数据库文件没有打开，则`get`函数会打开它。
* `get`函数返回文件中的下一个条目。
* `set`函数会打开文件，如果文件已经被打开，则将其反绕
  * `stayopen`参数设置为非0时，调用`get`函数后，文件亦然是打开的
* `end`函数用于关闭主机数据库文件

我们可以用以下函数在协议名字和协议编号之间进行映射

```c
#include <netdb.h>
struct protoent *getprotobyname(const char *name);
struct protoent *getprotobynumber(int proto);
struct protoent *getprotoent(void);
// 成功返回指针，出错返回NULL

void setprotoent(int stayopen);
void endprotoent(void);

struct protoent {
    char *p_name;
    char **p_aliases;
    int p_proto;
}
```

* 这几个函数的用法与上面一组是相同的

服务是由地址的端口号部分来表示的。每个服务由一个唯一的端口号来支持。可以使用以下函数来操作端口号和服务

```c
#include <netdb.h>
struct servent *getservbyname(const char *name,const char *proto);
struct servent *getservbyport(int port,const char *proto);
struct servent *getservent(void);
// 成功返回指针，出错返回NULL
void setservent(int stayopen);
void endservent(void);

struct servent {
    char *s_name;
    char **s_aliases;
    int s_port;
    char *s_proto;
    // ...
}
```

将一个主机名和一个服务名映射到一个地址
```c
#include <sys/socket.h>
#include <netdb.h>
int getaddrinfo(const char *restruct host,const char *restrict service,
					const struct addrinfo *restrict hint,
					struct addrinfo **restrict res);
// 成功返回0，出错返回非0错误码
void freeaddrinfo(struct addrinfo *ai);

struct addrinfo {
	int ai_flags;	// 定义行为
	int ai_family;	// 地址族
    int ai_socktype;	// socket类型
    int ai_protocol;	// 协议
    socklen_t ai_addrlen;	// 地址的长度
    struct sockaddr *ai_addr;	// 地址数据
    char *ai_canonname;	// 主机名
    struct addrinfo *ai_next;	// 下一个节点
    // ...
};
```

* 需要提供主机名、服务名，或者两者都提供。
* 如果只提供一个名字，另外一个必须是一个空指针。
* 主机名可以是一个节点名或点分格式的主机地址
* `hint`参数用来选择符合特定条件的地址，用于过滤地址的模板。

如果`getaddrinfo`调用失败，不能使用`perror`或`strerror`来生成错误码消息，而是调用下面这个函数生成错误消息

```c
#include <netdb.h>
const char *gai_strerror(int error);
// 返回描述错误的字符串饿指针
```

将地址转换成一个主机名和一个服务名的函数

```c
#include <sys/socket.h>
#include <netdb.h>
int getnameinfo(const struct sockaddr *restrict addr,socklen_t alen,
               char *restrict host,socklen_t hostlen,
               char *restrict service,socklen_t servlen,int flags);
// 成功返回0，出错返回非0
```

* `flags`参数的值提供了控制翻译的方式
  * `NI_DGRAM`：服务基于数据报而非基于流
  * `NI_NAMEREQD`：如果找不到主机名，将其作为一个错误对待
  * `NI_NOFQDN`：对于本地主机，仅返回全限定域名的节点名部分
  * `NI_NUMERICHOST`：返回主机地址的数字形式，而非主机名
  * `NI_NUMRICSCOPE`：对于IPv6，返回范围ID的数字形式，而非名字
  * `NI_NUMERICSERV`：返回服务地址的数字形式(即端口号)，而非名字