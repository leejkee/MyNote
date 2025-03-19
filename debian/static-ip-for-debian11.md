# 怎么在debian11中设置获取静态ip地址
如果你的电脑拥有以太网卡，你需要选择以下两种方法之一为其配置ip，这样电脑才能上网。  

1、最简单的方法就是使用动态主机配置协议DHCP(Dynamic Host Configuration Protocol)进行动态配置，他需要在局域网中有一个DHCP服务器，它可能提示需要主机名，对应的设置如下。然后DHCP服务器才会向主机发送合适的网络配置。
- DHCP 配置(`/etc/network/interfaces`)
```shell
auto ens33
iface ens33 inet dhcp
    hostname leejk
```

2、使用“静态的”网络配置必须要详细地指出网络设置选项，这至少包含ip地址和子网掩码，有时候还需要指出广播地址和网络地址。指定连接到外部的路由器为网关。
- 静态的网络配置(`/etc/network/interfaces`)
```shell
auto ens33
iface ens33 inet static
    address 192.168.240.133
    broadcast 192.168.240.255
    network 192.168.240.0
    gateway 192.168.240.2
```

无线网络在使用之前需要安装相关固件，这些固件debian默认是没有安装的，需要先在apt源中添加`non-free`仓库。很多固件都是专有的，并且在这个仓库中都可以找到。然后安装`firmware-*`，后面填写你需要安装的包即可。如果你不知道你需要安装包的名字，你可以选择运行`isenkram-autoinstall-firmware`来安装硬件包。然后在`/etc/network/interfaces.d/`下创建对应无线网卡的配置文件即可。

参考文献：  
1. [debian-handbook](https://www.debian.org/doc/manuals/debian-handbook/sect.network-config)  
2. 谢希仁.计算机网络[M].电子工业出版社,2017.