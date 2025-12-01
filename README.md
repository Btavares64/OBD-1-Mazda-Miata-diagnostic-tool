# OBD-1-Mazda-Miata-diagnostic-tool

## Author 
- Brandon Tavares

## Vehicle Compatibility 
- NA Miata (1989-1993)
  
## Goal of Program
- Read blinks given by the Engine Control Unit and Airbag Module
- Decode the blink codes and display the message on the terminal
- Provide timer for the duration of code reset
- CLI to interact with device menu

## Hardware Needed
- Any Linux Distrobution
- Raspberry Pico

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

Go to pico-sdk directory
```
cd pico-sdk
```

Run 
```
git submodule update --init
```

Next, exit pico-sdk library by running
```
cd ..
```

Change Directory to the src folder
```
cd src
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
Ensure Pico is set to BOOTSEL before locating directory

Located the correct directory to copy blink.uf2
```
mount | grep RPI-RP2 | awk '{print $3}'
```
Flash the compiled program to the Raspberry Pico
```
sudo cp blink.uf2 <Result of the last command>
```

Launch Program in Minicom
```
sudo minicom -D /dev/ttyACM0 -b 115200
```

## Pico Wire Diagram

## References
- https://www.miata.net/garage/faultcodes.html
- https://www.mellens.net/mazda/Mazda-Miata-1991-1993/1991_wiring.pdf

