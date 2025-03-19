---
title: zsh的安装
date: 2022-02-04 21:23:38
tags:
- linux
- zsh
categories:
- 新的入门
- Shell
- zsh
---

Tips: The commands are all in archlinux platform.

## zsh的安装
*安装之前建议先`sudo pacman -Syu`进行更新
```shell
$ sudo pacman -S zsh
```
## 查看已安装的shell
```shell
$ chsh -l
```
or you can use `cat /etc/shells` to list the shells you have installed.

执行这条命令后，你可以看到类似以下的info：
```shell
[ljk@leejk ~]$ chsh -l
/bin/sh
/bin/bash
/usr/bin/git-shell
/bin/zsh
/usr/bin/zsh
```
## 更换默认的shell为zsh
```shell
$ sudo chsh -s /usr/bin/zsh
```
重新登录后进入打开konsole会显示第一次使用，可以按提示进行配置。配置完成后会在 **~/** 下生成 __.zshrc__ 配置文件。

## 配置zsh
切换shell后重新打开终端模拟器会提示对zsh进行配置，按 1 键就可以进入配置界面了：
```
Please pick one of the following options:
(1)  Configure settings for history, i.e. command lines remembered
     and saved by the shell.  (Recommended.)
(2)  Configure the new completion system.  (Recommended.)
(3)  Configure how keys behave when editing command lines.  (Recommended.）
(4)  Pick some of the more common shell options.  These are simple "on"
     or "off" switches controlling the shell's features.  
(0)  Exit, creating a blank ~/.zshrc file.
(a)  Abort all settings and start from scratch.  Note this will overwrite
     any settings from zsh-newuser-install already in the startup file.
     It will not alter any of your other settings, however.
(q)  Quit and do nothing else.  The function will be run again next time.
--- Type one of the keys in parentheses --- 
```
完成基本的zsh设置,使用cat查看配置文件内容如下：
```shell
leejk% cat .zshrc 
# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
bindkey -e
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall3131
zstyle :compinstall filename '/home/ljk/.zshrc'

autoload -Uz compinit
compinit
# End of lines added by compinstall
```

## 使用zsh+p10k的方案，个人倾向于轻量，oh-my-zsh是很强大的zsh插件管理器

### installation 
```shell
# themes
sudo pacman -S zsh-theme-powerlevel10k
# plugins
sudo pacman -S zsh-autosuggestions zsh-syntax-highlighting zsh-completions
```

### configration
#### 开启文件夹color
```shell
# in ~/.zhsrc
alias ls='ls --color=auto'
```

#### 启用p10k主题和三个补全插件
```shell
# in ~/.zhsrc
source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh
source /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh
source /usr/share/zsh-theme-powerlevel10k/powerlevel10k.zsh-theme
# 使用tab键显示命令的参数和作用
autoload -Uz compinit && compinit
```
