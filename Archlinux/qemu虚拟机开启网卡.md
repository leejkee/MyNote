# kvm/qemu在开启虚拟机时出现无法开机，并且提示virtual network default "Inactive"
- function 1
移除网卡再重新加进去
- function 2
```shell
sudo virsh net-list --all                                                 23:13:57
 Name      State    Autostart   Persistent
--------------------------------------------
 default   active   no          yes
# set the virtual network active
sudo virsh net-start default 
```