# KAOS

This repository contains a fully working x64 OS - with a lot of different bugs of course! ;-)

## How to use it

After fetching the whole repository, you have to build the build environment, which contains the custom-built GCC Cross Compiler for the x32 and x64 processor architecture.

```shell
cd main64/docker-buildenv
docker image build -t sqlpassion/kaos-buildenv:latest .
```

After the successful build (which can take a long time, around 45min on my AMD Ryzen system, and 90min on my 13" MacBook Pro 2019!), you can build the whole OS with the following command on Windows:

```shell
docker run --rm -it -v d:\GitHub\KAOS:/src sqlpassion/kaos-buildenv /bin/sh /src/main64/build.sh
```

And here is the correct build command line for a Mac OS or Linux environment:

```shell
docker run --rm -it -v $HOME/Documents/GitHub/KAOS:/src sqlpassion/kaos-buildenv /bin/sh /src/main64/build.sh
```

As you can see, the Docker container just mounts the local source code, and builds everything within the container. The container then exits and is also deleted.
The result of the build is the file `KAOS64.img` in the `main64` folder, which is a FAT12 formatted flopyy disk that you can mount into your Hypervisor as a bootable floppy disk to run the OS.

!!!CAUTION!!!
Currently the OS only works on VMware Fusion/VMware Workstation!
Hyper-V, and all the other Hypervisors are currently NOT working, don't ask me why...

## How to use the GUI

The OS also comes with a GUI - if you have build it accordingly ;-)
To enable the GUI support, you have to uncomment the following lines in the file `main64/boot/bootsector.asm`:

```shell
; Set the graphics mode to SVGA (1280 x 1024 - 64K Colors)
mov ax, 4F02h
mov bx, 0x411A
int 0x10
```

As the comment says, it enables the SVGA graphics mode.
And in addition you have to change the following variable to `1` in the file `main64/kernel/kernel.c`:

```shell
// Indicates if KAOS is executed with a GUI or in Text Mode
int UIMode = 1;
```

If you build the OS after these changes again, it should run afterwards with a GUI - if you are on VMware Fusion.
On VMware Workstation the GUI version doesn't work.