#!/bin/sh

/usr/lib/rc/sv.d/sysfs		start
/usr/lib/rc/sv.d/procfs		start
/usr/lib/rc/sv.d/devfs		start
/usr/lib/rc/sv.d/cgroups	start
/usr/lib/rc/sv.d/root		start
/usr/lib/rc/sv.d/hostname	start
/usr/lib/rc/sv.d/hwclock	start
/usr/lib/rc/sv.d/kmod-static-nodes start
/usr/lib/rc/sv.d/tmpfiles-dev	start
/usr/lib/rc/sv.d/udev		start
/usr/lib/rc/sv.d/udev-trigger	start
/usr/lib/rc/sv.d/modules	start
/usr/lib/rc/sv.d/udev-settle	start
/usr/lib/rc/sv.d/console-setup	start
/usr/lib/rc/sv.d/net-lo		start
/usr/lib/rc/sv.d/misc		start
/usr/lib/rc/sv.d/remount-root	start
/usr/lib/rc/sv.d/mount-all	start
/usr/lib/rc/sv.d/swap		start
/usr/lib/rc/sv.d/random-seed	start
/usr/lib/rc/sv.d/tmpfiles-setup	start
/usr/lib/rc/sv.d/sysusers	start
/usr/lib/rc/sv.d/dmesg		start
/usr/lib/rc/sv.d/sysctl		start
/usr/lib/rc/sv.d/binfmt		start
/usr/lib/rc/sv.d/cleanup	start

sleep 5
