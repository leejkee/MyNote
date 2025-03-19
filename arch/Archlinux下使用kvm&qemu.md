intel支持虚拟化
```shell
$ LC_ALL=C lscpu | grep Virtualization
Virtualization:                  VT-x
```
内核支持虚拟化技术
```shell
$ zgrep CONFIG_KVM /proc/config.gz
CONFIG_KVM_GUEST=y
CONFIG_KVM_MMIO=y
CONFIG_KVM_ASYNC_PF=y
CONFIG_KVM_VFIO=y
CONFIG_KVM_GENERIC_DIRTYLOG_READ_PROTECT=y
CONFIG_KVM_COMPAT=y
CONFIG_KVM_XFER_TO_GUEST_WORK=y
CONFIG_KVM=m
CONFIG_KVM_INTEL=m
CONFIG_KVM_AMD=m
CONFIG_KVM_AMD_SEV=y
CONFIG_KVM_XEN=y
CONFIG_KVM_MMU_AUDIT=y
```
内核模块已导入
```shell
$ lsmod | grep kvm              
kvm_intel             352256  0
kvm                  1073152  1 kvm_intel
irqbypass              16384  1 kvm
```
```shell
$ lsmod | grep virtio                                    23:47:29
virtio_balloon         28672  0
virtio_scsi            28672  0
virtio_blk             20480  0
virtio_net             65536  0
net_failover           24576  1 virtio_net
```
__如果virtio不显示则手动导入__
in /etc/modules-load.d/virtio-net.conf
```shell
virtio-net
virtio-blk
virtio-scsi
virtio-serial
virtio-balloon
```

```shell
# qemu | network | uefi support
sudo pacman -S qemu ebtables dnsmasq bridge-utils openbsd-netcat edk2-ovmf
# manager with gui
sudo pacman -S libvirt virt-manager virt-viewer
```
调整权限，将自己加入libvirt组  
`sudo vim /etc/polkit-1/rules.d/50-libvirt.rules`
```shell
# add this in file
/* Allow users in kvm group to manage the libvirt
daemon without authentication */
polkit.addRule(function(action, subject) {
  if (action.id == "org.libvirt.unix.manage" &&
    subject.isInGroup("kvm")) {
      return polkit.Result.YES;
  }
});
```
当前用户加入kvm组  
`sudo usermod -a -G kvm $(whoami)`

启动服务
```shell
sudo systemctl enable libvirtd.service
sudo systemctl start libvirtd.service
sudo systemctl start virtlogd.service
```