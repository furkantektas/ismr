#!/bin/sh

echo "Building start.cpp"
make all


echo "Building 3DModel"
cd 3DModel
make all

echo "Building opencv-stream-overlay"
cd ../opencv-stream-overlay/
make all
