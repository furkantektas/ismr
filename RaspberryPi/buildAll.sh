#!/bin/sh

echo "Building sendip"
make all

echo "Building Rover5/driver"
cd Rover5
make all
