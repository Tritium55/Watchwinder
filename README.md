# Watchwinder
Watch winder for mechanical watches with three slots.

This is a [watch winder/ "Uhrenbeweger"](https://de.wikipedia.org/wiki/Uhrenbeweger) project.
The watch winder itself is able to wind 3 watches. The amount of turns per day, aswell as the desired time of day, can be set within the user interface.

## Parts
1. Arduino Uno
2. DS3231 real time clock
3. 3 Servos                     //TODO add name of servo/ serial number
4. 1.77 inch SPI TFT Display 128x160 pixel
5. 3 MOSFETs                    //TODO add some info
6. All [printed parts](3D-Printed-Parts) needed
7. M2 threaded inserts and M2 screws

## 3D-Printing
All required parts are printed in PLA with 20% infill and without supports.
This makes the printing process very reliable, even on older machines.
All threaded inserts must be inserted with considerable heat.
I recommend using a soldering iron set to 250-300°C and some gentle pressure.

## Connection Information
### [RTC (Real Time Clock)](Data-Sheets/Clock)
- 3.3V
- GND
- SDA to analog 4
- SCL analog 5
- SQW/INT to pin 2

### [1.77" Display](Data-Sheets/1.77_TFT_Display)
- 5V
- GND
- MISO to pin 12
- SCK to pin 13
- MOSI to pin 11
- LCD CS to pin 10
- SD CS to pin 4
- D/C to pin 9
- BL to +5V

### Servos
- //TODO

### Interface
- //TODO

## Libraries
// TODO
The following libraries need to be downloaded. This can be done within the Arduino IDE:
- Adafruit RTC Library
- TFT
- Adafruit GFX Library
- Adafruit ST7735 Library
- SPI (arduino avr core)


## Loading the Firmware
The build process is as follows:

After making sure, that you have the [Arduino IDE](https://www.arduino.cc/en/software) installed, you need to download the needed [Libraries](#libraries) from within the IDE.
After that, connect the Arduino to your PC, install the necessary [drivers](https://support.arduino.cc/hc/en-us/articles/4411305694610-Install-or-update-FTDI-drivers) if it didn't happen automatically, and select the USB Port the Arduino is connected to. 
Now open the [main.ino](Code/main/main.ino) and click upload in the top left corner.
You have now completed the Firmware step.

Note: You will need to download the [main folder](Code/main) and either open the folder itself or open the [main.ino](Code/main/main.ino) from within the folder.


