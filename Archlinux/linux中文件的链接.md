# 关于linux中硬链接和符号链接（软链接，Symbolic Link）
## 硬链接
通过索引节点链接。  
保存在磁盘中的文件会被分配一个编号，称为索引节点号。  
硬链接允许一个文件有多个有效路径名。  
删除原文件也不会对文件有影响，除非所有与之有关的硬链接都被删除。  
## 软链接
使用文本文件存储了原文件的位置信息。
原文件被删除，软链接也随之失效。

# 使用方法
假定原文件为`~/file`
- 为file创建硬链接f
```shell
# the directory where you want to create the hard link for ~/file
cd <dir>
# create the link
ln /home/user/file f
```

- 为file创建软链接fs
```shell
ln -s /home/user/file fs
```
# 我的应用
写一个一键编译并运行c程序的脚本，然后软链接到/usr/bin/下，原位置的文件修改/usr/bin/下的脚本也会被更改，便于修改
```shell
$ cat /usr/bin/runc                                                  
#!/bin/bash

gcc main.c && ./a.out
$ cat scripts/runC                                                   
#!/bin/bash

gcc main.c && ./a.out

# info of symbolic link
~/scripts $ ls -li /usr/bin/runc                                       
5021509 lrwxrwxrwx 1 root root 24 May 20 14:25 /usr/bin/runc -> /home/lhame/scripts/runC
```