---
title: 使用systemd管理network
date: 2022-03-26 09:58:43
tags: 
- linux
- arch
- systemd-networkd
categoryes:
- Archlinux
- installtion
---
# Archlinux，使用systemd-networkd管理网络
## 1、DHCP
### dhcpcd
使用`dhcpcd`可以自动为机器分配ip，并配置DNS，网关  

希望dhcpcd开机自动启动，可以使用
```shell
sudo systemctl enable dhcpcd
```
### systemd-networkd
本文记录systemd-networkd管理的方法。  
使用systemd，需要在`/etc/systemd/network/`下创建`.network`文件  

- 无线网络可以使用
```shell
sudo vim /etc/systemd/network/25-wireless.network
```
内容如下：
```shell
[Match]
Name=wlan0

[Network]
DHCP=yes
```
- 有线网络可以把网卡名换为有线网卡名称：
```shell
[Match]
Name=ens33

[Network]
DHCP=yes
```
文件内容的Name需要你自己使用 `ip a` 命令查看无线网卡或者有线网卡的接口名称，一般无线网卡以w开头，有线网卡常以e开头。

最后，你需要启动`systemd-resolved`服务，它用于解析DNS域名
```shell
sudo systemctl enbale systemd-resolved
```

# 2、Static
希望配置静态ip，则需要修改Network内容，在`/etc/systemd/network/20-wireless.network`文件中写入：
```shell
[Match]
Name=wlan0

[Network]
Address=10.1.10.9/24
Gateway=10.1.10.1
DNS=10.1.10.1
```
依次写入IP，网关，和DNS服务器地址。
最后同样设置systemd-resolved开机自启
```shell
sudo systemctl enbale systemd-resolved
```