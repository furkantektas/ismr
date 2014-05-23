#!/bin/sh
# starting raspberry camera stream at http://RASPBERRYIP:8090 

sudo killall raspivid >/dev/null 2>/dev/null & 
sudo killall clvc >/dev/null 2>/dev/null  &
sleep 5

raspivid -o - -t 0 -hf -vf -w 640 -h 480 -fps 15 | cvlc stream:///dev/stdin --sout '#standard{access=http,mux=ts,dst=:8090}' :demux=h264