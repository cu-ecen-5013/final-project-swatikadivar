#!/bin/sh
ifconfig wlan0 10.233.174.16   #Set the static IP address, should be unique
wpa_passphrase SSID  PASSWD> /etc/wpa_supplicant.conf
route add default gw 10.233.174.254  #Router IP address
wpa_supplicant -B -i   wlan0    -c    /etc/wpa_supplicant.conf
echo “nameserver 8.8.8.8” >> /etc/resolv.conf
echo “nameserver 10.233.174.254” >> /etc/resolv.conf
: exit 0
