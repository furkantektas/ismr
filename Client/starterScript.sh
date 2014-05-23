#!/bin/sh

if [ $# -ne 4 ]
then
    echo "Invalid Argument Count"
    echo "Syntax: $0 STREAMADDRESS AUGMENTATIONPORT IP DRIVERPORT"
    exit
fi

echo "Opening video stream, that may take a while (up to 1 min)"
cd opencv-stream-overlay/
./opencv-stream-overlay $1 $2 >../logs/stream.log 2>../logs/streamerrors.log &

sleep 30
echo "Opening Model"
cd ../3DModel
./model $3 $4 >../logs/model.log 2>../logs/modelerrors.log & 