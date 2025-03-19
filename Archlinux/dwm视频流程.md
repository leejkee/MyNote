# ArchLinux下使用 __dwm__
__写在前面：__
我想我不需要解释为什么使用dwm，有想折腾的，有觉得轻量用地很舒服的，有抱着学习一下试一试的心态去接触的......总之每个人都有不同的看法，无需和其他wm或者de相互比较，大家用的开心就好。  

[dwm](https://dwm.suckless.org/)是一个窗口管理器，你可以理解为诸如gnome类的桌面环境，它被称为动态窗口管理器。
## 安装需要的依赖
- xorg(和显示图形界面有关的协议)
```shell
sudo pacman -S xorg-server xorg-xinit xorg
```
- 字体  
中文字体和英文字体，以及一些图标的字体（nerd fonts），代码字体
```shell
sudo pacman -S noto-fonts-cjk wqy-microhei adobe-source-code-pro-fonts ttf-nerd-fonts-symbols ttf-jetbrains-mono
```
## 然后是我想啰嗦的一些
考虑到也许吧，可能会有人看到我的视频，写一些有关linux的基础的东西，想起来啥就补啥。
- git  
下面使用到的git clone其实是在后面那个网址去下载它的项目源码到本地，我这里是没有加什么参数的，所以在什么目录执行这个命令，源码就下载到这个目录下的一个和项目同名的文件夹里面，比如我下面安装dwm的其实就下载到了一个名为dwm的目录下
- wget,curl一些下载工具  
一个下载软件的命令行工具，使用linux下的cli（命令行）软件可以节省很多时间，就是前期入门比较麻烦。  
比如我要下载dwm的透明补丁
```shell
wget https://dwm.suckless.org/patches/alpha/dwm-alpha-20201019-61bb8b2.diff
```
- 善于使用tab补全机制
很多情况下，比如在终端里，打一部分的命令，然后使用tab键可以直接补全命令，比如输入`pac`，可以直接补全为`pacman`,在默认的shell(bash)中，如果遇到键入的命令前缀有多个匹配项，则再按一次tab会列出这些选项。  
不光是命令补全，更多的用到的是补全这个文件目录下的文件名，下载的一些图片文件文件名都很长，比如需要删除某个文件，可以
```shell
rm <文件名>
```
这个文件名就可以不用打全，打个开头然后tab一下就可以利用补全机制

## 其他软件  
我使用的终端：Alacritty(arch下使用pacman直接安装)
```shell
sudo pacman -S alacritty
```
dwm里面我同样推荐的终端：
同样c语言编写的Terminal——`st`(simple terminal)  
下载源码，使用git下载源码
```shell
git clone https://git.suckless.org/st
```
```shell
cd st && sudo make clean install
```

## 安装dwm
_*安装之前请先安装依赖部分*_  

官方原版
```shell
git clone https://git.suckless.org/dwm
```
没有打任何补丁，所以安装启动后是一个最基础版的dwm，但是我们喜欢折腾的总是想要好看点的效果。这些在最后面写。
## 启动dwm需要的一些配置
- 创建`~/.xinitrc`文件
```shell
vim ~/.xinitrc
```
并写入`exec dwm`
- 启动dwm  
终端输入`startx`
## 安装一些基本的软件
如果在之前已经安装了st，那么进入dwm后直接按`Alt Shift Enter`打开一个终端。
- 安装dmenu，一个搜索软件的软件
```shell
git clone https://git.suckless.org/dmenu
cd dmenu && sudo make clean install
```
按`Alt p`启动dmenu

## 怎么为dwm打补丁
一些好看的效果和一些好用的功能都可以以打补丁的形式添加到你的dwm。
我习惯于把补丁全部存放在`~/patches/`文件夹下，以透明补丁为例：
```
mkdir ~/patches && cd patches
wget https://dwm.suckless.org/patches/alpha/dwm-alpha-20201019-61bb8b2.diff
```
然后进入dwm的目录，使用patch命令：
```
cd ~/dwm/
patch < ~/patches/dwm-alpha-20201019-61bb8b2.diff
```
如果你下载了我的[dwm](https://github.com/leejkee/dwm_matebook13)，会发现我也采用了up主The CW的建议，删掉了config.def.h文件，不然打完了补丁在编译就会报错，因为补丁是修改了config.def.h,删掉了config.def.h,就会提示找不到它，让你指定这个config.def.h,直接输入config.h就可以了。
## 怎么显示状态栏
dwm社区提供有对应补丁，我没有选择补丁，能不打补丁就不打补丁，本人比较懒。
dwm安装后，使用
```shell
 xsetroot -name "abcd"
```
右上角的dwm-6.3会变成abcd，也就是我们添加的字符
这样我们可以写一个脚本，把需要的信息整合到一个字符串中，然后写到这个命令，同时每2s刷新一次即可完成状态栏实时显示。
具体写法可以参考[我的修改](https://github.com/leejkee/scripts1)，以及这个写法的原作者的[项目](https://github.com/joestandring/dwm-bar)。我的修改版是我目前正在使用的，目前是改动了会及时同步，所以会和原版出入较大。  
我只需要电池显示，亮度显示，声音显示，时间显示，所以我实际上只用到了四个脚本，如果你需要其他显示项，可以在根目录下的`dwm_bar.sh`文件中去掉对应的注释选项以打开对应选项显示。
## 和状态栏有关的
autostart这个补丁，需要打上，以便于把一些需要开机启动的东西放在这个脚本里面，而不是`.xinitrc`文件中


