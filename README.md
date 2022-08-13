# Astronode uart

## Description
This repository holds the source code for sending commands to the astronode device.

The astronode is a communication terminal from astrocast. <br>
[Astrocast webite](http://www.astrocast.com) <br>
[Serial command documentation](https://docs.astrocast.com/docs/products/astronode-api/commands-definition) <br>
[Astronode device](https://www.astrocast.com/products/astronode-s-plus/) <br>
[Astrocast github](https://github.com/orgs/Astrocast/repositories) 

## Dependencies
The software currently runs only on Linux. <br>
* libasio-dev from libboost. apt-get install libboost
* google test.

## Build

Debug build
```
cmake -DCMAKE_BUILD_TYPE=Debug -B cmake-build-debug
cmake --build cmake-build-debug --target astroUart_run
```

Fake serial build
```
cmake -DCMAKE_BUILD_TYPE=Release -DFAKE_SERIAL_BUILD=1 -B cmake-build-serial_fake
cmake --build cmake-build-serial_fake --target astroUart_fake_serial
```

## Run
example: 
./astroUart_run /dev/ttyUSB3

## Test