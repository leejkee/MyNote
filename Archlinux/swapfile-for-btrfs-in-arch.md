# 在btrfs文件系统上为archlinux创建swapfiles

## swapfile的作用
- 扩展物理内存

- archwiki上的介绍  
Swap space can be used for two purposes, to extend the virtual memory beyond the installed physical memory (RAM), and also for `suspend-to-disk` support.

## 创建方法

- 创建一个swap子卷  
```shell
sudo btrfs su cr /swap
```

- 创建一个大小为0的swapfile  
```shell
cd swap
sudo truncate -s 0 swapfile
```

- 修改权限  
```shell
sudo chmod 0600 swapfile
```

- 格式化swapfile
```shell
sudo mkswap swapfile
```

- 开启swapfile
```shell
sudo swapon swapfile
```

- 写入fstab文件，开机自动启动
```shell

# Static information about the filesystems.
# See fstab(5) for details.

# <file system> <dir> <type> <options> <dump> <pass>

# /swapfile
/swap/swapfile        none        swap        defaults      0 0
```
以上的有关swapfile的内容可供参考，但是必须在之前挂载主分区
