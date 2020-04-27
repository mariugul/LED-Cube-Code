# LED Cube Code for Arduino or Standalone Atmega328 (*Under Contruction)
[![License badge](https://img.shields.io/github/license/mariugul/LED-Cube-Code)](https://github.com/mariugul/LED-Cube-Code/blob/master/LICENSE)
[![GitHub last commit](https://img.shields.io/github/last-commit/mariugul/LED-Cube-Code)](https://github.com/mariugul/LED-Cube-Code/commits/master)
[![GitHub issues](https://img.shields.io/github/issues/mariugul/LED-Cube-Code)](https://github.com/mariugul/LED-Cube-Code/issues)



This project contains the code for a LED cube, using an Arduino board or the Atmega328 as a standalone with Atmel Studio. It's the code supporting the graphical programming tool [LED Cube Code Generator 3D](https://github.com/mariugul/LED-Cube-Code-Generator-3D). Supporting video tutorials found at [YouTube](). 

### Why? What's the difference?
The Arduino board is constructed with the microchip Atmega328. However, to program the chip on an Arduino board, one usually programs it with the Arduino IDE using the Arduino framework. This _can_ be limiting, because the Arduino framework is an abstraction layer that causes the Atmega328 to run slower than its potential. In a LED cube, speed is very important as well as memory for the light patterns. These reasons led the motivation to write the code in **C**. This gave a better and more efficient code, not using the Arduino framework. However, the code is **fully compatible** with the Arduino board and can be uploaded with the Arduino IDE. The project was based on using the bootloader inside the Arduino board to upload the code. However, it's entirely possible with little to no effort to upload the code to a standalone Atmega328, using Atmel Studio.

### Arduino Framwork?
When programming Arduino, to control the Input/Output (IO) pins, one uses `digitalWrite(HIGH)` / `digitalWrite(LOW)`. These functions are part of the Arduino class, which is fundamentally a **C++** class. While convenient, `digitalWrite()` is 15-30 times slower than manipulating the IO pins directly in **C** as intended by Atmel. This is done by bitshifting e.g. `PORTB0 |= (1 << PIN0)`. The second part of the Arduino framework issues has to do with interrupts. Arduino uses its own `millis()` function to keep track of time. For this to work, an interrupt routine has to run in the background, even if you do not utilize `delay()` or interrupts in your code. This disturbs the timing and contributes to a less efficient LED cube.

For the reasons above and because the sole purpose of a LED cube is to quickly turn IO pins on/off, the Arduino framework was not used, in order to produce a more efficient and accurate LED cube.

## Arduino <img src="https://cdn.iconscout.com/icon/free/png-512/arduino-4-569256.png" alt="" width="40"/>
Do you wish to use the Arudino IDE and not Atmel Studio? Read on.

#### Development Board
There will be no actual "Arduino Code" written. Keep in mind that "Arduino Code" is merely C++, with Arduino's functions from the class that the Arduino creators developed. Most of the code that you write on an Arduino is usually merely C code anyway, so there isn't a huge difference. If you plan to use your Arduino board, look at this board as a development board for the Atmega328. This board has a crystal (clock), USB port and a programmer, among other things. So in the case you were to buy a standalone Atmega328, you would have to buy all these parts and connect them somehow, but you don't need that!

#### Bootloader
The Arduino board has another advantage, the Atmega328 on it comes with a bootloader. This means that there exists a tiny program on the chip that can easily upload code from your computer with a USB cable. It's not that easy with standalone chips. This is a very convenient thing that is going to be expoited in this project.

#### Arduino IDE
So what about the Arduino IDE? The cool thing about the bootloader and the IDE is that they are developed to work together. Just open the project in the IDE and flash the code, it's _that_ simple.

## Atmel Studio <img src="https://www.it.unlv.edu/sites/default/files/styles/250_width/public/sites/default/files/assets/software/icons/atmel_studio.png?itok=Y_BrK5R2" alt="" width="30"/>
Do you wish to use Atmel Studio with or without an Arduino board? Read on.

#### Arduino Board
If you are using the Arduino board, the bootloader on the chip will be utilized for uploading and it works just as simply as the Arduino IDE.
TODO: Add how to set up Arduino upload.

#### Standalone Atmega328
If you don't have an Arduino board, you will need a programmer. Configure Atmel Studio according to the type of programmer you have, and upload the code.

## Tools
**[Arduino IDE]()**

**[Atmel Studio]()**

## The Code
How does the code work? If you are interested in how the code actually works, read on. If you don't care, it's still gonna work :)

#### Modules
These are the files in this project.
* gpio.h
* pattern.h
* timer.h and .c
* main.c

TODO: Finish code explanation.

## License
This project is licensed under the MIT license and is open source. You are free to use this project as you wish as long as you credit the work. See the [LICENSE](LICENSE) file for details.

## Contributing
If you want to contribute that's great! Send a pull request and I will review it.

## Previous Version
The first version of the LED cube code was written entirely on Arduino. This code uses lots of nested `for()` and `while()` loops and `delay()`. It's simple and it works. The code, corresponding code generator and instructions can be found at [Instructables](https://www.instructables.com/id/LED-CUBE-CODE-4x4x4-Arduino/) <img src="https://logodix.com/logo/1584749.png" alt="" width="20"/>. Who wrote the Arduino code is not known to me, however I made the code generator application.    

## Authors
Marius C. K. Gulbrandsen
