# installation
```shell
sudo pacman -S plasma-pa plasma-desktop dolphin sddm
```

# nvidia drive
like kernel `linux`, if u use `linux-zen`, the `dkms` should be installed.
```shell
sudo pacman -S nvidia-utils nvidia nvidia-settings 
sudo mkinitcpio -P
```

# config
## 网络
使用networkmanager, plasma-nm(system tray needed), network-manager-applet(tray based on GTK)
```shell
sudo pacman -S networkmanager plasma-nm
```

## terminal

```shell
sudo pacman -S kitty
```

## system monitor (discarded)
```shell
sudo pacman -S plasma-systemmonitor
```  
## net speed show on the bar (simple and helpful)
```shell
sudo pacman -S plasma6-applets-netspeed
```

## theme
切换主题保存原有布局配置文件