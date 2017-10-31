# Solar Plant Monitoring System
![Build Status](https://travis-ci.org/carlosb/celeste.svg?branch=master)

The system consists in obtaining data from "Solar Plants" which produce electricity
and send relevant data, like power consumption, to the cloud. From there, we can
choose to cut the power or detect faulty devices.

![diagram](diagrams/SolarPanels.png)

# Building
One can build the celeste server by creating another directory and just using cmake:
````
mkdir build
cd build
cmake ..
make -j4
````

# About
This software is licensed under the AGPL.
