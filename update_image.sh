#!/bin/bash

sudo /sbin/losetup /dev/loop0 floppy.img
sudo mount /dev/loop0 /mnt2
sudo cp kernel /mnt2/kernel
sudo umount /dev/loop0
sudo /sbin/losetup -d /dev/loop0
