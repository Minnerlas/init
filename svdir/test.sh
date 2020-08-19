#!/bin/sh

END=10
for i in $(seq 1 $END)
do 
	echo $i
done

echo $PWD
echo $USER
echo $SHELL
# vim

while true
do
	sleep 10
done

#
# 01-sysfs              30-udev           65-swap
# 02-procfs             31-udev-trigger   70-random-seed
# 03-devfs              32-modules        75-tmpfiles-setup
# 04-cgroups            33-udev-settle    80-sysusers
# 05-root               40-console-setup  85-dmesg
# 10-hostname           45-net-lo         90-sysctl
# 15-hwclock            50-misc           95-binfmt
# 20-kmod-static-nodes  55-remount-root   99-cleanup
# 25-tmpfiles-dev       60-mount-all
