#!/bin/sh
set -e
. ./iso.sh

unset GTK_PATH # not doing this every system reboot causes qemu to throw symbol lookup error
qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom myos.iso
