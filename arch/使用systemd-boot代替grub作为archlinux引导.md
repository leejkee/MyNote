---
title: 使用systemd-boot代替grub作为archlinux引导
date: 2022-03-03 12:10:34
tags:
- linux
- systemd-boot
- grub
- arch
categories:
- Archlinux
- installation
---

# 使用archlinux自带的systemd-boot去引导系统开机
注意：下面假定你的电脑已经使用 __grub__ 方案，那么如何替换成 __systemd——boot__ 是本文记录的主要内容。如果你恰好刚刚准备在虚拟机或者你的个人PC上安装Archlinux，那么本文也将作为可参考文章；如果你是linux新手，建议先尝试ubuntu，你将很平滑地从Windows过度到GNU/linux。   
此外，使用gpt格式是必须的，因为需要磁盘唯一标识符uuid。

## 删除grub
```shell
$ pacman -Rns grub
```
执行这条命令将会删除boot分区内grub的配置文件。
## 配置systemd
### 首先！！！
再三确认你的efi分区，也就是boot分区的盘符，使用 `sudo fdisk -l` 你可以查看到你的硬盘分区情况和磁盘大小情况。你会得到类似以下输出:
```shell
Device             Start       End   Sectors   Size Type
/dev/nvme0n1p1      2048    206847    204800   100M EFI System
/dev/nvme0n1p2    206848 451387391 451180544 215.1G Linux filesystem
/dev/nvme0n1p5 451387392 463970303  12582912     6G Linux filesystem
/dev/nvme0n1p6 463970304 975677439 511707136   244G Linux filesystem
```
通常符号为1的盘符代表efi分区。
### 然后，bootctl install
```shell
$ bootctl --path=/boot install
```
注：命令中表示路径的参数可去，如果挂载点有不同请自己指定绝对路径。  

执行后开始配置启动文件
```shell
[ljk@leejk ~]$ cat /boot/loader/loader.conf
default arch
timeout 4
console-mode 0
editor no
```
cat命令用于显示文件内容，将以上文件内容写入`/boot/loader/loader.conf`，你可以使用vim编辑器，执行`sudo vim /boot/loader/loader.conf`。  

配置完成后配置arch.conf
```shell
[ljk@leejk ~]$ sudo cat /boot/loader/entries/arch.conf
title GNU/Linux_arch
linux /vmlinuz-linux
initrd /intel-ucode.img
initrd /initramfs-linux.img
options root=
```
同样使用`sudo vim /boot/loader/entries/arch.conf`将以上内容写入`/boot/loader/entries/arch.conf`，默认该文件不存在，是需要自己创建的，写入该内容后，进入vim的普通模式（insert模式下按esc回到普通模式），再按 `:` 进入命令行，执行`:r!blkid /dev/nvmen1p6` ,其中 __/dev/nvmen1p6__ 你需要修改为你的根目录盘符，然后通过修改，留下PARTUUID后面的内容，得到类似以下的格式：
```shell
[ljk@leejk ~]$ sudo cat /boot/loader/entries/arch.conf
title GNU/Linux_arch
linux /vmlinuz-linux
initrd /intel-ucode.img
initrd /initramfs-linux.img
options root=PARTUUID=66276022-7f25-8a45-bb00-5f60abcd660a rw
```
到此systemd-boot管理的引导方式配置结束。
## 使用btrfs格式的arch.conf
如果不使用ext4文件类型，使用btrfs类型，那么在最后的options行后面除了写上对应root目录的uuid之外，还需要指定子卷@。
```shell
options root=PARTUUID=<UUID> rootflags=subvol=@ rw
```
## 疑难解答
### boot目录下文件丢失
如果不小心删去了boot分区的文件，那么会导致开机无法出现引导项，无法开机，需要使用livecd进入archiso，虽然这对arch新手不是很友好。
将你之前安装arch的启动盘重新插入电脑的usb接口，然后按F12或者esc（不同厂商电脑不一样）选择u盘启动进入livecd，也就是你安装arch使用的哪个u盘的系统，里面包含很多工具，在联网后执行：  
（虚拟机用户：关机后在开机下面的小三角展开选择 __打开电源进入固件__。选择包含IDE字样的选项即可进入。）
```shell
$ mount /dev/根分区 /mnt #将根分区（也就是你安装系统的那个分区）挂载到/mnt下
$ mount /dev/EFI分区 /mnt/boot #将EFI分区挂载到根分区的/boot下
$ arch-chroot /mnt #进入archiso
$ pacman -S linux #安装内核，会重新在/boot生成被删除的内核文件
#如果你恰好没有安装intel-ucod，按照我的配置会报错，执行
$ pacman -S intel-ucode
```
### bootctl install提示未找到EFI分区
这是因为没有设置EFI分区的type为EF00，推荐使用gdisk或者cgdisk进行设置
在gdisk创建分区的时候会提示选择code，输入相应code即可。
