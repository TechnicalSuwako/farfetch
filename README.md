# farfetch

![](https://this.is.very.dangerous.software/2024-06-20-114921_1920x1080_scrot.png)

## インストールする方法 | Installation
### OpenBSD
```sh
make
doas make install
```

### NetBSD | FreeBSD | Dragonfly BSD
```sh
make
sudo make install
```

### CRUX
```sh
sudo prt-get bmake
bmake
sudo bmake install
```

### Void
```sh
sudo xbps-install bmake
bmake
sudo bmake install
```

### Artix
```sh
sudo pacman -S base-devel bmake
bmake
sudo bmake install
```

### OmniOS
```sh
gcc -Wall -Wextra -O3 -I/usr/include -o farfetch main.c src/*.c src/logo/*.c -L/usr/lib -lc
sudo cp farfetch /usr/bin
sudo cp farfetch.1 /usr/bin/share/man/man1
```

### Debian | Devuan | Ubuntu | Linux Mint | PopOS
[Kazuhikoさん](https://social.076.moe/conversation/1127279#notice-2122922)
```sh
sudo apt install -y build-essential bmake git pciutils
bmake
sudo bmake install
```

### Fedora | Red Hat | CentOS | Rocky Linux
```sh
sudo dnf install bmake clang
bmake
sudo bmake install
```
