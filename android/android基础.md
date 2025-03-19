---
title: android基础
date: 2022-04-11 16:58:38
tags:
- Android
- 物联网
categories:
- 新的入门
- Android
---
# 在archlinux上使用Android Studio完成物联网安卓app开发
## installation
```
sudo pacman -Ss android-studio
```
查看当前的`android-studio`的版本，同时确保包名输入无误。  
安装：
```shell
sudo pacman -S android-studio
```
## 第一次启动
第一次启动会提示找不到`android SDK`，会提示下载，默认下载路径：
`~/Android/Sdk/`.  
下载完成即可看到new页面，有 __Create a new project__ 字样。

## 安装java jdk(x86_64的机器)
安装jdk1.8，关于jdk命名规则，请自行Google or [Bing](cn.bing.com)  
在arch下安装jdk很简单，只需要：
```shell
sudo pacman -S jre8-openjdk jdk8-openjdk
```
实际上安装jre8的时候会顺便安装jdk8，为了不必要麻烦直接一道命令搞定。  
使用`java -version`显示jdk版本号即表示安装完成，
```shell
$ java -version
openjdk version "1.8.0_332"
OpenJDK Runtime Environment (build 1.8.0_332-b04)
OpenJDK 64-Bit Server VM (build 25.332-b04, mixed mode)
```

## Android Studio简介
新建一个项目，可以看到项目文件夹很复杂，我们的关注重点是名为`app`的文件夹，里面会包含java源码，使用XML描述的android布局配置文件等。
## Android UI
### Activity的生命周期
#### 生命周期的四个状态
- Active/Running  
新的Activity入栈，处于栈顶，可见，和用户交互的激活状态。
- Paused  
失去焦点，已经不可与用户交互，但是仍然可见。
- Stopped  
该Activity被另一个Activity完全覆盖，不可见被隐藏，内存不足时则被强行终止。
- Killed
删除掉处于Paused和Stopped状态的Activity

#### 生命周期的三个循环
- 整个生命周期
从onCreate()到onDestory()
- 可见的生命周期
从onStart()到onStop()
- 前台的生命周期
从onResume()到onPause()

## Create an Activity
使用New project创建一个empty Activity。  
- 描述布局的XML文件路径：`app/src/main/res/layout/activity_main.xml`
- java源码文件路径：`app/src/main/java/`，可以看到以包名命名的文件夹下的`MainActivity.java`。

