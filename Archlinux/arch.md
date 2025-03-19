<!--
 * @Author: leejkee
 * @FilePath: \undefinedc:\Users\CWW\Desktop\useless_note\arch\arch.md
 * @Date: 2022-05-29 22:02:54
 * @LastEditTime: 2022-05-29 22:05:47
 * @Description: 
-->
# 安装arch Linux的主要思路
截图为VMware16 pro中的演示
## 安装前准备
下载archlinux的livecd，理论上使用manjaro的livecd或许也可以，还是习惯使用arch自带的only cli的livecd（仅命令行无桌面）
### EFISTUB
```shell
pacman -S efibootmgr
efibootmgr --disk /dev/nvme0n1p1 --part 1 --create --label "Arch Linux" --loader /vmlinuz-linux-lts --unicode 'root=PARTUUID=fcad510d-7553-4565-a458-c4a952f0eb9e rw initrd=\initramfs-linux-lts.img' --verbose
```

