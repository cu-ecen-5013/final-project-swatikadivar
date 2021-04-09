#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

DESCRIPTION = "Socket server application for Yocto build."
SECTION = "socketserver"
DEPENDS = ""
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=3da9cfbcb788c80a0384361b4de20420"

PV = "1.0+git${SRCPV}"
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

SRCREV = "c6f27b4e1ae55c3002c620fd52a796d6c3abb18e"
SRC_URI = "https://github.com/cu-ecen-5013/final-project-swatikadivar/tree/master/socketserver"

S = "${WORKDIR}/git"

#inherit autotools


FILES_${PN} += "${bindir}/socketserver"
# TODO: customize these as necessary for any libraries you need for your application
TARGET_LDFLAGS += "-pthread -lrt"
inherit update-rc.d
INITSCRIPT_PACKAGES= "${PN}"
INITSCRIPT_NAME_${PN}="socketserver-start-stop"


do_configure () {
	:
}

do_compile () {
	oe_runmake
}

do_install () {
	# TODO: Install your binaries/scripts here.
	# Be sure to install the target directory with install -d first
	# Yocto variables ${D} and ${S} are useful here, which you can read about at 
	# https://www.yoctoproject.org/docs/latest/ref-manual/ref-manual.html#var-D
	# and
	# https://www.yoctoproject.org/docs/latest/ref-manual/ref-manual.html#var-S
	# See example at https://github.com/cu-ecen-5013/ecen5013-yocto/blob/ecen5013-hello-world/meta-ecen5013/recipes-ecen5013/ecen5013-hello-world/ecen5013-hello-world_git.bb

	install -d ${D}${bindir}
	install -m 0755 ${S}/socketserver ${D}${bindir}/	
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/socketserver-start-stop ${D}${sysconfdir}/init.d
}









# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""
