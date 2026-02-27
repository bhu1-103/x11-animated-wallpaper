#!/bin/bash

killall xwinwrap
xwinwrap -argb -fs -fdt -b -nf -- ./build/wallpaper %WID &
