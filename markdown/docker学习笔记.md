# docker学习笔记

最近公司的项目需要用到docker容器技术，所有就把docker学习的一些笔记记了下来，方便后面查询和复习。

> Docker 是一个开源的应用容器引擎，让开发者可以打包他们的应用以及依赖包到一个可移植的容器中，然后发布到任何流行的 Linux 机器上，也可以实现虚拟化。容器是完全使用沙箱机制，相互之间不会有任何接口。

### docker安装

* Debian安装

    1. 编辑/etc/apt/sources.list文件，添加下面一句话

            deb http://http.debian.net/debian jessie-backports main
    
    2. 然后执行 apt-get update 更新源
    3. 安装docker.io包

            sudo apt-get install docker.io

    4. 测试

            sudo docker run --rm hello-world

    5. 如果想不使用root权限直接运行docker命令的话，可以执行下面这句话：
       
        	sudo usermod -aG docker 你的用户名

		然后重新登陆一下账户就可以了
	6. 开启docker后台服务
			
			sudo service docker start

### 基础知识

#### docker常用命令

* 在容器中运行程序，示例：

		docker run ubuntu:15.10 /bin/echo "hello world"

	参数解释：    
	1. run： 运行一个容器
	2. ubuntu：15.10 指定要运行的镜像，Docker首先从本地主机上查找是否存在，如果不存在就会从Docker Hub中下载公共镜像
	3. /bin/echo "hello world"：在启动的容器中要执行的命令

* 命令 docker ps
	
> 查看当前运行的docke容器
	
* 命令 docker logs [容器ID或容器名称]
	
> 查看容器的标准输出 
	
* 命令 docker stop [容器ID或容器名称]
	
> 停止正在运行的容器
	
* 命令 docker port [容器ID或容器名称]
	
> 查看指定容器的端口映射
	
* 命令 docker images
	
> 列出本机上的所有镜像
	
* 命令 docker rm [容器ID]
	
> 删除停止状体的容器
	
* 命令 docker rmi [镜像名称]
	
> 删除本机中的镜像
	
* 命令 docker pull [镜像名称]
	
> 下载镜像到本机
	
* 命令 docker search [镜像名称]
	
> 查找镜像
	
* 命令 docker save [options] [image]
	
> 将指定镜像保存成tar归档文件
	
* 命令 docker import [options] [file|URL|-] [ImageName[:tag]]
	> 将镜像归档文件转换成镜像  
	> options选项：  
	> 1. -c：应用docker指令创建镜像  
	> 2. -m：提交时的文字说明  
	> 这俩参数我基本不用(lll￢ω￢)

#### docker run命令行参数解释

* 参数 -i -t
	> 这两个参数一起时候可以让docker运行的容器实现“对话”的功能

	示例
		
		docker run -i -t ubuntu:15.10 /bin/bash
	参数解析：  
	1. -i： 允许你对容器内的标准输入进行交互
	2. -t： 在新的容器中指定一个伪终端或终端  
	
	运行了这句命令后，实际上我们已经进入到了容器中，我们就可以在容器中执行各种命令，当然，前提是当前容器中有该命令。  
	如过要退出当前容器，可以使用Ctrl+D来推出容器

* 参数 -d
	> 以后台模式运行容器

	示例：
		
		docker run -d ubuntu:15.10 /bin/sh -c "while true,do echo hello world;sleep 1;done"

	只想上面的这条命令可以看到并没有一直打印 "hello world"字样，而是出现了一串字符串，这个字符串是容器ID，是唯一的。
  
* 参数 -P 
	> 将容器内部使用的网络端口映射到我们使用的主机上

	示例：
		
		docker run -d -P training/webapp paython app.py

	然后使用docker ps查看容器运行的信息 ports那一列就会多出来一条信息
	意思是将容器内部的端口映射到本地主机的端口号上

### 创建镜像

> 有两种方式创建镜像：
>   
> 1. 从已经创建的容器中更新镜像，并且提交镜像
> 2. 使用Dockerfile指令来创建新的镜像

#### 更新镜像

1. 先进入要更新的容器内（使用-t命令）
2. 执行apt-get update命令进行更新（你可以执行自己想要添加的东西）
3. 然后退出容器 
4. 通过docker commit命令来提交容器副本

		docker commit -m="update" -a="cxldada" e12dx93434 cxldada/update:v2

	参数解释：
	1. -m：提交的描述信息
	2. -a：指定镜像的作者
	3. e12dx93434：容器的ID
	4. cxldada/update:v2 ： 指定要创建的目标镜像名

#### 使用Dockerfile指令创建镜像

> 使用这种方式创建镜像时，我们需要创建一个Dockerfile文件，其中包含了一些指令，用来构建我们的镜像

* Dockerfile文件指令  
	1. FROM
		> 第一条指令必须是FROM指令，如果同一个Dockerfile文件中创建多个镜像，可以使用多个FROM指令,格式：

			FROM <image>或者FROM <image>:<tag>

	2. MAINTAINER
		> 制定维护这信息,格式：

			MAINTAINER <name>

	3. RUN
		> 有两个格式分开来说：
		
			RUN <command>

		> 这种格式是在shell终端中运行的
		
			RUN ["executable","param1","param2"]

		> 这种格式是使用exec执行，也就是说第一种格式实在本机的shell中运行的，而第二种格式实在容器环境中运行的
	
	4. CMD
		> 制定容器启动后要执行的命令，一般都是早就写好的脚本，例如：CMD["/run.sh"]	
		> 
		**注意：如果文件中指定了多个命令，则只执行最后一条命令，如果用户启动时加了命令，则会覆盖掉CMD指定的命令**

	5. EXPOSE
		> 告诉Docker服务端要暴露的端口号，供互联系统使用。在启动容器时需要通过-P，Docker主机会自动分配一个端口转发到指定的端口

		格式：

			EXPOST 9200 9300

	6. ENV
		> 1. 创建时候给容器加一个环境变量
		> 2. 指定一个值，为或许的RUN指令服务

	7. ADD
		> 将复制指定的文件到容器中的指定位置

		格式：

			ADD <src> <dest>
		
 源文件必须在Dockerflie文件所在位置的相对路径
		
	8. COPY
	
	> 复制本地的文件或目录到容器中。路劲不存在时会自动创建
		
9. ENTRYPOINT
		
	> 配置容器启动后执行的命令，并且不会被命令参数所覆盖，只能有一个ENTRYPOINT指令，多个时，只有最后一个才会生效
		
	10. WORKDIR
		
		> 定义工作目录，如果容器中没有此目录，会自动创建

还有一些命令我还没有用过，这里就不做介绍，需要的朋友可以去google一下，抱歉了！

* 根据Dockerfile文件构建镜像

		docker build -t cxldada/ubuntu:15.16 .

	-t：指定要创建的目标镜像名  
	**注意最有有个参数 . 这表示当前目录 不要忘记了**