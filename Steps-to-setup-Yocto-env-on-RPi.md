1. Clone Poky using Git:
````
git clone -b dunfell git://git.yoctoproject.org/poky
````

2. switch to poky directory and Clone meta-raspberrypi:
````
cd poky
git clone -b dunfell git://git.yoctoproject.org/meta-raspberrypi
````

3. Initialize the build Environment:
````
source oe-init-build-env
````

4. Add meta-raspberrypi to BBLAYERS in conf/bblayers.conf:
````
BBLAYERS ?= " \
  /home/skadivar/swatikadivar-aesd-assignments/final-project-swatikadivar/poky/meta \
  /home/skadivar/swatikadivar-aesd-assignments/final-project-swatikadivar/poky/meta-poky \
  /home/skadivar/swatikadivar-aesd-assignments/final-project-swatikadivar/poky/meta-yocto-bsp \
  /home/skadivar/swatikadivar-aesd-assignments/final-project-swatikadivar/poky/meta-raspberrypi \
  "
````  
  
5. Open conf/local.conf and change MACHINE to raspberrypi, raspberrypi0,raspberrypi2 or raspberrypi3 depending on your Raspberry Pi model:
````
MACHINE ??= "raspberrypi3"
````

6. Append the following line to conf/local.conf to set GPU memory in megabytes:
````
GPU_MEM = "16"
````  

7. Build a minimal image of a GNU/Linux distribution for your Raspberry Pi:
````
bitbake core-image-base
````
