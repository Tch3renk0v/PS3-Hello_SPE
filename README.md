# PS3-Hello_SPE
A simple multithreaded hello world program to check toochain and access to spe.

# Requirements
To compile this program, you will first need a working gcc toolchain for the cell.
You can compile it from source (tricky) or use prebuild packages like those from fedora 9 and debian wheezy.
This code has been tested using gcc-4.7 toolchain.

Next you will need the libspe2. You can build it from source or grab package available from fedora-devel iso for the cell. 

Assure that spufs is active in your target system linux kernel got spufs and that a /spu is mounted as a spufs filesystem. 
You can do it by adding an entry in your fstab file (/etc/fstab in general) like:
```
spufs /spu spufs defaults 0 0
```
or by running the equivalent (non persistent) command : 
```
mount -t spufs spufs /spu
```

# Compilation:
compile by simply running
```
make
```

If everything went fine you should obtain something like this:
```
./Hello.exec
Hello from spe : (0x10746008)
Hello from spe : (0x10746458)
Hello from spe : (0x10746680)
Hello from spe : (0x10746230)
Hello from spe : (0x10746ef8)
Hello from spe : (0x10747120)
Hello from spe : (0x10746cd0)

The program has successfully executed.
```
This output mean you have access to all your spe (7 in this example) and that they are very polite.


