#!/bin/sh

cp ./kernel/output/kernel.iso ./testenv/kernel.iso
cd ./testenv || exit

# debug flag: -d

if [ "$1" = "debug" ]; then
    echo "debug mode"
    qemu-system-x86_64 -nodefaults -readconfig ./qemuConfig.cfg -smp 4 -device usb-kbd \
                      -cpu Opteron_G1-v1,pdpe1gb=on \
                      -netdev user,id=n1,hostfwd=udp:127.0.0.1:1234-:1234,hostfwd=tcp:127.0.0.1:1234-:1234 \
                      -object filter-dump,id=f1,netdev=n1,file=dump.dat -device e1000e,netdev=n1 \
                      -s -S -daemonize
else
  echo "no debug mode"
  qemu-system-x86_64 -nodefaults -readconfig ./qemuConfig.cfg -smp 4 -device usb-kbd \
                     -cpu Opteron_G1-v1,pdpe1gb=on \
                     -netdev user,id=n1,hostfwd=udp:127.0.0.1:1234-:1234,hostfwd=tcp:127.0.0.1:1234-:1234 \
                     -object filter-dump,id=f1,netdev=n1,file=dump.dat -device e1000e,netdev=n1
fi
