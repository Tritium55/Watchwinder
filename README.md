# Watchwinder
Watchwinder for mechanical watches with three slots


## Parts
1. Arduino Uno
2. DS3231 real time clock
3. 3 Servos                     //TODO add name of servo/ serial number
4. 1.77 inch SPI TFT Display 128x160 pixel


## Libraries
// TODO
The used libraries need to be downloaded from the Arduino IDE.
They are as follows:
- RTClib by Adafruit - for the realtime clock


## Connection Information
### Clock
- 3.3V
- GND
- SDA to analog 4
- SCL analog 5

### Display
- 5V
- GND
- MISO to pin 12
- SCK to pin 13
- MOSI to pin 11
- LCD CS to pin 10
- SD CS to pin 4
- D/C to pin 9
- BL to +5V

### Interface
- //TODO