# farfetch

![](https://this.is.very.dangerous.software/2024-06-20-114921_1920x1080_scrot.png)

## インストールする方法 | Installation
### OpenBSD | NetBSD | FreeBSD
```sh
make
doas make install
```

### CRUX
```sh
doas prt-get bmake
bmake
doas bmake install
```

### Void
```sh
doas xbps-install bmake
bmake
doas bmake install
```

### Artix
```sh
doas pacman -S base-devel bmake
bmake
doas bmake install
```

### Debian | Devuan | Ubuntu | Linux Mint | PopOS
[Kazuhikoさん](https://social.076.moe/conversation/1127279#notice-2122922)
```sh
doas apt install -y build-essential bmake git pciutils
bmake
doas bmake install
```
