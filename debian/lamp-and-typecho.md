# 使用debian11在本地配置lamp架构的web应用组和typecho博客框架
## 先知
1、what is the lamp?  
lamp is Linux, Apache, Mariadb and Php/Perl/Python.  
2、what is typecho?  
Typecho is a light and efficient website frame.

## debian11(There are two options to chooes.)
- install debian11 on your PC
- purchase a VPS and a domain

## install debian 11 in Windows 10 by [vmware16](https://www.vmware.com/products/workstation-pro/workstation-pro-evaluation.html).
- 配置apt的软件源，请参考北外的debian的[bullseye版本的源配置帮助](https://mirrors.bfsu.edu.cn/help/debian/).  
- Then, run this:(Make sure you login in by 'root')
```shell
apt update
apt upgrade
```

## 安装apache2(Make sure you login in by 'root')
```shell
apt install apache2
```
如果在安装系统时勾选了web server，apache2已经默认安装好了。
## 安装php
```shell
apt install php
```
phpmyadmin是typecho需要的管理数据库的工具。
## 安装mariadb数据库服务
```shell
apt install mariadb-server
```
## 对数据库进行简单配置并为typecho创建一个管理用户和数据库
### 进行安全性设置
```shell
mysql_secure_installation
```
进入安全设置交互，并进行以下设置：  
- 为root用户设置密码
- 选择不切换到unix_socket
- 选择是否重置密码
- 选择移除匿名用户
- 选择禁止远程登陆
- 选择删除测试用的数据库
- 选择重新加载权限表
```shell
root@debian:/home/lee# mysql_secure_installation

NOTE: RUNNING ALL PARTS OF THIS SCRIPT IS RECOMMENDED FOR ALL MariaDB
      SERVERS IN PRODUCTION USE!  PLEASE READ EACH STEP CAREFULLY!

In order to log into MariaDB to secure it, we'll need the current
password for the root user. If you've just installed MariaDB, and
haven't set the root password yet, you should just press enter here.

Enter current password for root (enter for none):
OK, successfully used password, moving on...

Setting the root password or using the unix_socket ensures that nobody
can log into the MariaDB root user without the proper authorisation.

You already have your root account protected, so you can safely answer 'n'.

Switch to unix_socket authentication [Y/n] n
 ... skipping.

You already have your root account protected, so you can safely answer 'n'.

Change the root password? [Y/n] Y
New password:
Re-enter new password:
Password updated successfully!
Reloading privilege tables..
 ... Success!


By default, a MariaDB installation has an anonymous user, allowing anyone
to log into MariaDB without having to have a user account created for
them.  This is intended only for testing, and to make the installation
go a bit smoother.  You should remove them before moving into a
production environment.

Remove anonymous users? [Y/n] Y
 ... Success!

Normally, root should only be allowed to connect from 'localhost'.  This
ensures that someone cannot guess at the root password from the network.

Disallow root login remotely? [Y/n] Y
 ... Success!

By default, MariaDB comes with a database named 'test' that anyone can
access.  This is also intended only for testing, and should be removed
before moving into a production environment.

Remove test database and access to it? [Y/n] Y
 - Dropping test database...
 ... Success!
 - Removing privileges on test database...
 ... Success!

Reloading the privilege tables will ensure that all changes made so far
will take effect immediately.

Reload privilege tables now? [Y/n] Y
 ... Success!

Cleaning up...

All done!  If you've completed all of the above steps, your MariaDB
installation should now be secure.

Thanks for using MariaDB!
```

## 安装phpMyAdmin
```shell
apt install phpmyadmin
```
在安装过程中会提示为选择一个被自动配置去运行phhmyadmin的web服务，按空格键选择apache2；然会提是否为phpmyadmin创建一个数据库，选择yes即可；之后为phpmyadmin数据库创建密码。

## 创建管理员用户和typecho数据库
```shell
mysql
```
输入`mysql`进入mariadb的cli交互：
```shell
root@debian:/home/lee# mysql
Welcome to the MariaDB monitor.  Commands end with ; or \g.
Your MariaDB connection id is 49
Server version: 10.5.15-MariaDB-0+deb11u1 Debian 11

Copyright (c) 2000, 2018, Oracle, MariaDB Corporation Ab and others.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

MariaDB [(none)]> 
```

创建名为`typecho`的数据库：
```shell
MariaDB [(none)]> create database typecho;
Query OK, 1 row affected (0.000 sec)
```

创建名为`lhame`的用户，并且设置密码为`123456`：
```shell
MariaDB [(none)]> create user 'lhame'@'localhost' identified by '123456';
Query OK, 0 rows affected (0.001 sec)
```

给lhame用户赋予typecho数据库的全部权限：
```shell
MariaDB [(none)]> grant all privileges on typecho.* to 'lhame'@'localhost';
Query OK, 0 rows affected (0.001 sec)
```
现在查询结果：
```mysql
MariaDB [(none)]> select user,host from mysql.user;
+-------------+-----------+
| User        | Host      |
+-------------+-----------+
| lhame       | localhost |
| mariadb.sys | localhost |
| mysql       | localhost |
| phpmyadmin  | localhost |
| root        | localhost |
+-------------+-----------+
5 rows in set (0.001 sec)
```
立即刷新权限表：
```shell
MariaDB [(none)]> flush privileges;
Query OK, 0 rows affected (0.000 sec)
```

## 下载typecho
```shell
# 需要将typecho解压到/var/www/html/目录下，这是apache2的文件目录，可以在/etc/apache2/site-enabled/下的.conf文件中修改
cd /var/www/html

wget https://github.com/typecho/typecho/releases/latest/download/typecho.zip

# 顺带安装unzip，用于解压
apt install unzip
# 解压typecho安装包
unzip typecho.zip
# 解压后文件目录
root@debian:/var/www/html# ls
admin  index.php  install  install.php  LICENSE.txt  typecho.zip  usr  var
```

## 配置typecho

如果提示为usr/uploads/设置可写权限，需要：
```shell
chmod -R 777 usr/uploads/
```

## 开始安装typech0
在浏览器输入debian虚拟机的ip，可以使用`ip a`查询ip，然后按照提示进行安装，并依次输入之前创建好的数据库信息，最后为自己的网站设置一个管理员用户就可以使用了。

## 配置防火墙
使用ufw进行管理：
### 安装ufw
debian默认没有安装ufw，需要自行安装：
```shell
apt install ufw
```
安装后如果在bash仍然提示 __bash: ufw: command not found__，在bashrc中加入`export PATH=/usr/sbin:$PATH`

### 开启ssh、http、https端口
```shell
ufw allow OpenSSH
ufw allow 'WWW Full'
ufw enable
```
至此结束。
