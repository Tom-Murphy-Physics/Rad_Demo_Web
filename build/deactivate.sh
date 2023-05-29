#!/bin/sh
ids="$(xdotool search --onlyvisible --name Rad_Demo)"
for i in $ids; do
	xdotool windowsize "$i" 1000 500
	xdotool windowmove "$i" 0 0
done
wmctrl -r :ACTIVE: -b toggle,above
