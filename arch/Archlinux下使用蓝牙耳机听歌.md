---
title: dwm下使用蓝牙耳机听歌
date: 2022-03-20 13:01:22
tags:
- linux
- arch
- bluetooth
- dwm
categories:
- Archlinux
- dwm
- bluetooth
---
dwm不同于其他de，要使用蓝牙耳机，需要安装蓝牙协议栈以及蓝牙控制软件，并且需要额外安装`pulseaudio-bluetooth`。
## installation
```shell
sudo pacman -S  pulseaudio-bluetooth bluez bluez-utils
```
## Connection
开启蓝牙服务
```shell
sudo systemctl enbale bluetooth #开机自启
sudo systemctl enbale bluetooth #开启
```
连接蓝牙，bluez-utils提供了cli交互软件`bluetoothctl`
```shell
bluetoothctl #进入cli交互，所有选项均可使用tab补全
$ power on #开启
$ scan on #开始扫描
$ scan off #结束扫描
$ devices #列出可用设备，左边mac地址，右边设备名
$ pair <your mac addr> #配对mac地址
$ connect <your mac addr> #连接设备
$ exit #退出
```
每次开机或者重新登录都需要重新连接，下次重新连接无需配对，只需要`power on`和`connect`。