#!/bin/sh
ids="$(xdotool search --onlyvisible --name Rad_Demo)"
for i in $ids; do
	xdotool windowsize "$i" 350 875
	xdotool windowmove "$i" 1500 225
done
clear
wmctrl -r :ACTIVE: -b toggle,above
