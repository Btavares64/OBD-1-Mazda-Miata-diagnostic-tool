# OBD-1-Mazda-Miata-diagnostic-tool

## Author 
- Brandon Tavares

## Goal of Program
- Read blinks given by the ECU of from NA Miata (1989-1996)
- translate blinks and send the result to a webserver for the user to read
- reset code
- website to interact with the diagnostic tool

## Hardware Needed
- Any Linux Distrobution
- Raspberry pico

## Preparing your Raspberry Pico

Clone Repository by running 
```
git clone https://github.com/Btavares64/OBD-1-Mazda-Miata-diagnostic-tool.git
```

Go to project directory
```
cd OBD-1-Mazda-Miata-diagnostic-tool
```

Clone pico-sdk library
```
git clone https://github.com/raspberrypi/pico-sdk.git
```

Clone Free RTOS library
```
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel
```

Go to pico-sdk directory
```
cd pico-sdk
```

Run 
```
git submodule update --init
```

Next you to exit pico-sdk by running
```
cd ..
```

Change Directory to the projects folder
```
cd project
```

Install the nessesary packages in order to run the program
```
sudo apt install gcc-arm-none-eabi
```

```
sudo apt install build-essential
```

```
sudo apt install cmake
```

```
sudo apt install minicom
```

This next chain of commands will create a build environment to compile the 
project
```
mkdir build; cd build; cmake ..; make
```

Flash the compiled program to the Raspberry Pico
```
sudo cp blink.uf2 /media/$(whoami)/RPI-RP2
```

Launch Program in Minicom
```
sudo minicom -D /dev/ttyACM0 -b 115200
```

## Installing Hardware

## References
- https://www.miata.net/garage/faultcodes.html

