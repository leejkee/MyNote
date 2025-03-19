这篇记录也是我第一次正式记录archlinux安装过程的note，安装在btrfs文件系统上，是我最新尝试的内容，因为它应该是大势所趋。
# 系统的安装

## 分区
使用gpt分区表
```shell
cgdisk /dev/sda
```

大概可以看到这样的输出部分
```shell
root@archiso ~ # fdisk -l

Device       Start       End   Sectors   Size Type
/dev/sda1     2048   1050623   1048576   512M EFI System
/dev/sda2  1050624 976773119 975722496 465.3G Linux filesystem
```

## 创建子卷
我只创建home子卷，其他的默认在root下。  
在这之前需要将作为系统分区的`/dev/sda2`挂载到`/mnt`下。
```shell
mkfs.fat -F 32 /dev/sda1
mkfs.btrfs /dev/sda2
```
- create the subvol=@
```shell
btrfs su cr /mnt/@
```
- create the subvol=@home
```shell
btrfs su cr /mnt/@home
```
## 挂载子卷
```shell
umount /mnt
mount -o noatime,space_cache=v2,compress=zstd,ssd,discard=async,subvol=@ /dev/sda2 /mnt
mkdir /mnt/home
mkdir /mnt/boot
mount -o noatime,space_cache=v2,compress=zstd,ssd,discard=async,subvol=@home /dev/sda2 /mnt/home
mount /dev/sda1 /mnt/boot
```
## 安装系统
```shell
pacstrap /mnt base linux linux-firmware
```
这些都是需要安装的最基本的部分，包含最基本的系统，内核以及固件。
## 生成fstab
```shell
genfstab -U /mnt >> /mnt/etc/fstab
```
## 为mkinitcpio添加btrfs模块，并重新生成initramfs，如果你有多硬盘组raid，否则可跳过该步骤
这里需要进入chroot：`arch-chroot /mnt`
```shell
vim /etc/mkinitcpio.conf
```
在module()中添加btrfs
like this:
```shell
# vim:set ft=sh
# MODULES
# The following modules are loaded before any boot hooks are
# run.  Advanced users may wish to specify all system modules
# in this array.  For instance:
#     MODULES=(piix ide_disk reiserfs)
MODULES=(btrfs)
```
重新生成initramfs
```shell
mkinitcpio -p linux
```
## 安装引导程序
常用的引导程序有grub，system-boot，这里记录grub安装过程，因为system-boot过程已经在[我的blog](https://lhame.top/index.php/archives/14/)记录。
```shell
pacman -S grub grub-btrfs efibootmgr 
```
安装grub
```shell
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=Arch
```
生产grub配置文件
```shell
grub-mkconfig -o /boot/grub/gurb.cfg
```
在这步骤之前，你需要确保安装了内核`linux`，添加btrfs选项后并重新生成initramfs，并且其中的EFI分区路径填写的是/boot，实际上是/dev/sda1挂载到了/boot，所以确保EFI分区成功挂载也是必要的。
至此基本的系统安装已经完成。


# 对安装好的系统进行一些基本的设置
这部分其实可以编写脚本进行，其中包含时钟时区、主机名、语言支持、系统显示语言等选项，对于我而言这些设置都是几乎不需要作任何改变的，这里记录还是一步一步进行，有关的脚本后面可能会编写并上传到我的GitHub。
## 为root用户重新设置密码
在chroot环境下，还没有创建任何用户，所以是以root用户登录的，我们需要更新root用户的密码，以便重启之后登录。
```shell
passwd
```
`passwd`用于重置用户密码，后面跟用户即可重置该用户的登录密码。
## 为系统开启英文和中文的支持
```shell
nvim /etc/locale.gen
```
取消`en_US.UTF-8 UTF-8`,`zh_CN.UTF-8 UTF-8`,`zh_TW.UTF-8 UTF-8`三部分前面的注释
重新生成locale
```shell
locale-gen
```
设置系统显示语言为英文
```shell
echo LANG=en_US.UTF-8 >> /etc/locale.conf
```
## 设置主机名
为你的机器取名，编辑`/etc/hostname`，在第一行加入你的主机名  
或者使用`echo "<your hostname>" >> /etc/hostname`   
主机域名解析
编辑`/etc/hosts`文件，并添加以下内容：
```shell
127.0.0.1	localhost
::1		localhost
127.0.1.1	myhostname.localdomain	myhostname
```
最后一行的myhostname替换为你设置的主机名即可。
## 安装一些必要的软件
我需要使用ssh连接到我的虚拟机，并且文本编辑器是必要的，我正在入门neovim和vim，nano对于初学者是足够的友好。
```shell
pacman -S neovim nano openssh  
```
安装dhcpcd，无论后面使用静态ip还是动态分配
```shell
pacman -S dhcpcd
```
安装一些开发工具包
```shell
pacman -S git base-devel
```
## 添加一个普通用户，并且赋予其可以使用sudo特权的权限
```shell
useradd -m -G wheel lee
EDITOR=vim visudo
```
在visudo后打开的文件中，取消`%wheel ALL=(ALL) ALL`前面的注释，保存并退出。
## 使一些服务可以开机自启（也可以开机后手动开启，这一步不是必须的）
```shell
systemctl enable sshd
systemctl enable dhcpcd
```


参考文献：  
[1] [Arch Wiki Installation Guide](https://wiki.archlinux.org/title/Installation_guide).  
[2] [Tech it out Blog](https://www.nishantnadkarni.tech/posts/arch_installation/).  
[3] [nerdstuff.org](https://www.nerdstuff.org/posts/2021/2021-001_arch_linux_btrfs_systemd-boot/).  