#!/bin/sh

SERVERIP=10.1.97.85
SERVERPORT=7578
DRIVERPORT=4546

sleep 15
sh /home/pi/startstream.sh >logs/stream.log 2>logs/streamerrors.log &
/home/pi/sendip  $SERVERIP $SERVERPORT &
/home/pi/Rover5/driver $DRIVERPORT >logs/driver.log 2>logs/drivererrors.log &

echo "All Done!"