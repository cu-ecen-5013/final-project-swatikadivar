Start by adding Yocto base from our assignment repo : 

This specifies the base repository at https://github.com/cu-ecen-5013/yocto-assignments-base.git 
````
git remote add yocto-assignments-base https://github.com/cu-ecen-5013/yocto-assignments-base.git
````

````
git fetch yocto-assignments-base
````

make your master branch match the master branch of yocto-assignments-base
````
git merge yocto-assignments-base/master
````
This command clones the assignment-autotest submodule and nested git repositories. (not compulsory if not planning to use existing testcases)
````
git submodule update --init --recursive
````

Install all required packages in ubuntu to establish Yocto environment.
````
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
>      build-essential chrpath socat cpio python3 python3-pip python3-pexpect \
>      xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev \
>      pylint3 xterm
````

Add meta-raspberrypi(for raspberrypi machine), meta-openembedded(for meta-python and meta-networking - required for WiFi) and poky.
````
git submodule add https://git.yoctoproject.org/git/meta-raspberrypi meta-raspberrypi
````
````
git submodule add https://git.openembedded.org/meta-openembedded meta-openembedded
````
````
git submodule add git://git.yoctoproject.org/poky poky
````

Edit build.sh to specify image type to be generated, packages to be added to an image, add required meta layers etc. This all specifications will be added to conf/local.conf.

````
./build.sh
````

build.sh execution will take several hours. This will execute below command internally after updating local.conf.
````
bitbake core-image-base
````
Once execution completes without any issue, it will create an image at build/tmp/deploy/images/<machine_name>/<image_type_specified> depending on the type specified in build.sh file.

Flash this image on SD card and bring up RaspberryPi with the image flashed on SD card.
