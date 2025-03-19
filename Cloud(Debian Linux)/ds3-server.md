## Dark Souls 3私服流程
在国内厂商提供的云服务器上为黑暗之魂3提供联机服务，方便低延迟联机游玩

### 购买云服务器
- 配置 2核的CPU就可以，内存2g就好了，带宽5Mbps即可，硬盘选最小的即可
- 服务器操作系统，选用Windows Server需要的硬件最低要求要比Linux高不少，所以推荐使用Linux，而且服务端也已经有Linux版了
- 本文使用 Debian12作为操作系统，购买的是阿里云的轻量级ECS, 合约31元/月，每月前200G流量免费
- 
### 配置服务器
- 网络配置
    - 访问规则需要打开ssh(22), http(80), TCP/UDP(50000,50010,50020,50050), 这些都在你的云服务器的web控制面板设置
    - 软件安装
        - steam service
        - Dark Souls 3 Server

网络和防火墙配置
```shell
#!/bin/bash

# 输出日志
echo "配置防火墙端口...开始"

# 允许 TCP 和 UDP 端口 50000、50010、50020、50050
for port in 50000 50010 50020 50050
do
    # 使用 ufw 配置 TCP 和 UDP
    echo "允许端口 $port 的 TCP 和 UDP 通信..."
    sudo ufw allow $port/tcp
    sudo ufw allow $port/udp
done

# 允许 SSH 的 22 端口
echo "允许 SSH 端口 22..."
sudo ufw allow 22/tcp

# 启用 UFW 防火墙
echo "启用防火墙..."
sudo ufw enable

# 查看防火墙状态
echo "防火墙状态："
sudo ufw status

echo "防火墙端口配置完成。"
```
安装steamcmd, 参考value官方[wiki](https://developer.valvesoftware.com/wiki/SteamCMD#Debian)
```shell
sudo apt update; sudo apt install software-properties-common; sudo apt-add-repository non-free; sudo dpkg --add-architecture i386; sudo apt update
sudo apt install steamcmd
```

安装Dark Souls 服务端
```shell
wget https://github.com/TLeonardUK/ds3os/releases/download/v0.42.0.0-main/linux.zip
sudo apt install unzip
unzip linux.zip -d linux
```
### 启动前配置
- 解决依赖，使用脚本运行Server，而不是给服务器的环境变量添加一堆东西
```shell
#!/bin/bash

SERVER_PATH="/home/ecs-user/linux/Server/Server"

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$(pwd)"

$SERVER_PATH
```
将以上内容写入Sever目录下的`launcher.sh`中

- 使用守护进程处理launcher的异常
```shell
sudo vim /etc/systemd/system/ds3server.service
```
写入以下内容
```shell
[Unit]
Description=Dark Souls Server
After=network.target

[Service]
User=ecs-user
Group=ecs-user
WorkingDirectory=/home/ecs-user/linux/Server
ExecStart=/bin/bash /home/ecs-user/linux/Server/launcher.sh
Restart=always
RestartSec=5
StandardOutput=append:/var/log/ds3server.log
StandardError=append:/var/log/ds3server_error.log
Environment="LD_LIBRARY_PATH=/home/ecs-user/linux/Server"

[Install]
WantedBy=multi-user.target
```

- 启动system服务
```shell
sudo systemctl daemon-reload 
sudo systemctl start ds3server.service 
```

### 疑难
- Server依赖两个so, 其中一个在Server目录中，还有一个是安装steamcmd之后的，如果你的服务器使用x64的操作系统，务必使用`linux64`下的`steamclient.so`
- 为你的服务器配置一些选项，需要你阅读官方教程进行配置，我列出一些作为参考
```
    "ServerDescription": "Dark Souls III server.",
    "ServerHostname": "",
    "ServerId": "",
    "ServerName": "Long may the sun shine",
    "ServerPrivateHostname": "",
    "StartGameServerPortRange": 50060,

```
重点配置hostname和privatehostname，一个是你服务器的（公网）ipv4，一个是内网地址，具体可以参考官方Discord的教程

### 请参考[官方Github地址](https://github.com/TLeonardUK/ds3os)