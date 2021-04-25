* To add new meta layer, first complete basic build.sh execution and establish working Yocto environment setup.

* To add new package/application, write C code for it and makefile to compile that C code. Also prepare relevent header files.

* Execute make command locally and clear all compilation errors.

* Commit these files to git.

* Create a new meta-xyz folder in home directory.
````
mkdir meta-xyz

cd meta-xyz

mkdir conf

cd conf

touch layer.conf --> *write down layer.conf*

cd ..

mkdir recipes-xyz

cd recipes-xyz

mkdir xyz

cd xyz

touch xyz_1.0.bb --> *write bitbake file as per requirement*
````

execute below to add new layer to bblayer.conf file.

````
source poky/oe-init-build-env

bitbake-layers add-layer ../meta-xyz/
````

* Develop new image with new meta layer added by executing ./build.sh command again.

* make sure execution prints meta-xyz in Build Configuration as below:

![build_configuration](https://user-images.githubusercontent.com/77517602/115980670-bdc70880-a54b-11eb-8a30-5a7b10a291be.PNG)
