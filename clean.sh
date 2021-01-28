#!/bin/sh
set -e
. ./config.sh

for PROJECT in $PROJECTS; do
  (cd $SRC_DIR/$PROJECT && $MAKE clean)
done

rm -rf sysroot
rm -rf isodir
rm -rf myos.iso
