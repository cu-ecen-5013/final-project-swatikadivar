LICENSE = "BSD-3-Clause"
SRC_URI = "file://setup-wifi.sh \ 
	  "
do_install () {
install -m 0755    ${WORKDIR}/setup-wifi.sh     ${D}${sysconfdir}/init.d
  
update-rc.d -r ${D} setup-wifi.sh start 99 2 3 4 5 .
}
  
MASKED_SCRIPTS = " \
setup-wifi \
"
