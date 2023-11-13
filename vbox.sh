#!/bin/bash

# delete old vm
VBoxManage unregistervm MyOS --delete
# creating vm and registering to see in gui
VBoxManage createvm --name MyOS --register

# ioapic
# VBoxManage modifyvm MyOS --ioapic on

# memory
# VBoxManage modifyvm MyOS --memory 4096 --vram 128

# hard drive
# VBoxManage createhd --filename MyOS/MyOS_DISK.vdi --size 1000 --format VDI
# hard drive controller
# VBoxManage storagectl MyOS --name "SATA Controller" --add sata --controller IntelAhci       
# VBoxManage storageattach MyOS --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium  MyOS/MyOS_DISK.vdi                

# disk contoller
VBoxManage storagectl MyOS --name "IDE Controller" --add ide --controller PIIX4       
VBoxManage storageattach MyOS --storagectl "IDE Controller" --port 1 --device 0 --type dvddrive --medium myos.iso       
VBoxManage modifyvm MyOS --boot1 dvd --boot2 disk

# remote desktop
# VBoxManage modifyvm MyOS --vrde on                  
# VBoxManage modifyvm MyOS --vrdemulticon on --vrdeport 10001

# start machine
VirtualBoxVM --startvm MyOS #--debug
