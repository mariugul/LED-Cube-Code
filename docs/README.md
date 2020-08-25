# LED Cube Code for Arduino or Atmega328
[![License badge](https://img.shields.io/github/license/mariugul/LED-Cube-Code)](https://github.com/mariugul/LED-Cube-Code/blob/master/LICENSE)
[![GitHub last commit](https://img.shields.io/github/last-commit/mariugul/LED-Cube-Code)](https://github.com/mariugul/LED-Cube-Code/commits/master)
[![GitHub issues](https://img.shields.io/github/issues/mariugul/LED-Cube-Code)](https://github.com/mariugul/LED-Cube-Code/issues)


This project contains the code for a LED cube, using an Arduino board or the Atmega328 as a standalone with Atmel Studio. The code was developed together with the [Cube 3D](https://github.com/mariugul/cube-3d) programming tool. Supporting video tutorials found at [YouTube]()(coming soon). 

## Supported Cubes
Currently this project supports a 4x4x4 LED cube.

## What's the difference between Arduino and Atmega328?
The Arduino board is constructed with the microchip Atmega328. However, to program the chip on an Arduino board, one usually programs it with the Arduino IDE using the Arduino framework. This _can_ be limiting, because the Arduino framework is an abstraction layer that causes the Atmega328 to run slower than its potential. In a LED cube, speed is very important, as well as memory for the light patterns. These reasons led the motivation to write the code in **C** rather than to use Arduino's **C++** framework. This gave a better and more efficient code. However, the code is **fully compatible** with the Arduino board and can be uploaded with the Arduino IDE. The project was based on using the bootloader inside the Arduino board to upload the code. However, it's entirely possible with little to no effort to upload the code to a standalone Atmega328, using Atmel Studio, if you don't wish to use an Arduino.

## Arduino Framwork?
When programming Arduino, to control the Input/Output (IO) pins, one uses `digitalWrite(HIGH)` and `digitalWrite(LOW)`. These functions are part of the Arduino class, which is fundamentally a **C++** class. While convenient, `digitalWrite()` is 15 to 30 times slower than manipulating the IO pins directly in **C** as intended by Atmel. This is done by bitshifting e.g. `PORTB0 |= (1 << PIN0)`. The second part of the Arduino framework issues has to do with interrupts. Arduino uses its own `millis()` function to keep track of time. For this to work, an interrupt routine has to run in the background, even if you do not utilize `delay()` or interrupts in your code. This disturbs the timing and contributes to a less efficient LED cube.

For the reasons above and because the sole purpose of a LED cube is to quickly turn IO pins on/off, the Arduino framework was not used in order to produce a more efficient and accurate LED cube.

## Arduino vs Atmel Studio
And IDE is an Integrated Developement Environment, meaning it's essentially a code editor with programming capabilities and usually some debug capabilities. 

### Arduino IDE
Arduino developed their own simple to use IDE for writing code and programming the boards. For beginners and quick development, it's an ok IDE but once you start getting serious, it's very limiting. It's hard to edit code efficiently and it doesn't have as much customizability. You can use it with an external code editor and simple use the Arduino IDE as the programmer if you wish. A better choice in my opinion, is to simply use Atmel Studio if you start to get serious about embedded development.

### Atmel Studio IDE
This is Atmel's own IDE created for development on their chips, like the Atmega328. It's gonna feel closer to being in Visual Studio and it's easier to work in than the Arduino IDE. It can be set up to use the AVRDUDE programmer, so that you can upload code to the board. TODO: Link to how to set up Atmel Studio programmer.

### Summary
So to summarize the differences. If you just want to upload the code and make it work, I would suggest sticking with the Arduino IDE. It's not necessary to write any code as it's already done, except for the pattern.h file to generate LED patterns. However, I highly recommend using the [Cube 3D](https://github.com/mariugul/cube-3d) software to generate this file. If you however wish to write some code yourself and want to get more into embedded development, I advice on checking out Atmel Studio.

## Code
### Pattern File
To generate a light show on the LED cube you only need to edit the file `pattern.h`. This is simply a header file `.h` with an array containing the patterns. The default file looks like below and turns all LEDs on and off at a 250ms interval.
```c
#ifndef __PATTERN_H__
#define __PATTERN_H__

// Includes
//---------------------------------
#include <stdint.h>        // Use uint_t
#include <avr/pgmspace.h>  // Store patterns in program memory

// Pattern that LED cube will display
//--------------------------------- 
const PROGMEM uint16_t pattern_table[] = {
     // Blink all LEDs every 250ms
     0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 250,
     0x0000, 0x0000, 0x0000, 0x0000, 250,
};
#endif
```


The array is defined as an `uint16_t`, meaning it stores 16 bit unsigned variables. This is to optimize the memory usage. Inside the array there are 5 variables on each code line. The first four of them are written in hexadecimal `0xFFFF`, these represent 16 LEDs and one plane. Hexadecimal representation is merely for compact code. The last variable `250` is represented in decimal because it represents the time in milliseconds that the particular codeline should be displayed for. This makes more sense in decimal rather than hexadecimal. When the code is compiled, it's compiled down to binary anyway, so it doesn't matter wether you write in decimal, hex or binary. To the computer it's still the same.
```c
//plane1  plane2  plane3  plane4  display time [ms]
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 250,
```

If the hex value `0xFFFF` is converted to binary it would be `1111 1111 1111 1111` where each bit represents one LED with the first LED starting from the right. If the bit is a `1` that particular LED will be on and if it is `0` it will be off. And that's the basic idea of how this system works and that's why a 16 bit variable will be the most optimized way of storing the patterns while still keeping it structured in planes. The time variable will of course be a 16 bit too and this is so that it's possible to (in theory) have 2^16 = 65 536ms = 65.5 seconds to display each codeline. At the time of writing this length is not possible but it will be in the future with a new revision of the code. However, most patterns will be displayed for less and much less than 1 second.

`const PROGMEM` is used to define the array as well. What `PROGMEM` does is to save the code in _program memory_ (flash) instead of SRAM memory. The reason for this is that the flash memory is bigger than the SRAM, meaning we can store more patterns in this memory. It has to be `const` because flash can only be read from once it's programmed and running.

While you can write this pattern file yourself, I have created a 3D animated tool that does this for you [Cube 3D](https://github.com/mariugul/cube-3d). I highly suggest using that when generating patterns as it's very time effective and it's easy to visualize what you want. Understanding what goes on behind the curtains is of course always useful. Especially if you encounter any problems and need to debug.

### Main Code
This section is meant to be purely informative on how the code works. It's not necessary to make the LED cube work but rather to provide insight into the code for those interested.
#### The Concept
The fundamental concept of the LED cube is that it's divided into planes and columns. This is a [multiplexing](https://en.wikipedia.org/wiki/Multiplexing?oldformat=true) method for reducing the amount of IO pins necessary. With a 4x4x4 cube that means 20 IO pins, where 4 of them ground each plane and 16 of them supply power to the columns. The code is constructed in the way that only _one_ single plane can be on at a time. This in turn means that every plane needs to be switched on and off at a time interval, giving the illusion that the LEDs on different planes are lit.

#### Interrupt Service Routine
The Atmega328 is an 8-bit microcontroller and only has 8-bit registers. Therefore it cannot switch more than 8 IO pins in one instruction. We need 20 IO pins and it's therefore necessary to set three ports which each has 8 pins accessible. The image below shows how the Arduino pins map to the ports `PORTB`, `PORTC` and `PORTD`.

<img src="https://content.arduino.cc/assets/Pinout-UNOrev3_latest.png" alt="" width=""/>

To switch the planes on and off an Interrupt Service Routine (ISR) is used. The ISR merely switches on and off the LEDs from a pre-calculated value that happens in the while loop. This is to reduce the amount of time spent in the ISR.

```c
// Interrupt Service Routine
ISR (TIMER1_COMPA_vect)
{
	// Switch on the LEDs for the current plane
	PORTB = port_b;
	PORTD = port_d;
	PORTC = port_c; // Port C is last because it turns on the plane also
}
```

As shown in the code above `PORTB` is set to be the value of `port_b` in the ISR. `PORTB` is a avr-library variable for setting the ports and `port_b` is calculated in the while-loop from the pattern table. Only when a plane and a column (or several columns) are on at the same time will a LED light up. Because `PORTC` contains IO pins that goes to both columns and planes, it comes last so the power is turned on in that instant all at once.

#### Calculation of Port Values
The code below is how the actual calculation of the port values are done. This is the value that sets the correct IO pins to high and low. 
```c
// Calculate port values
port_b =  (pattern_buf[current_plane] & PORT_B_MASK) >> SHIFT_PORT_B; 

port_c = ((pattern_buf[current_plane] & PORT_C_MASK) >> SHIFT_PORT_C) ^ PLANE_MASK[current_plane]; // XOR to find the current PLANE to turn on

port_d =  (pattern_buf[current_plane] & PORT_D_MASK); // Don't need a shift 
```
The `pattern_buf[current_plane]` is an array holding one pattern line from the pattern table. It loads upon start and when the current pattern is finished displaying. The `current_plane` makes sure only one plane is selected at a time. The array will then return a hex value e.g. `0xFFFF`. The `PORT_B_MASK` variable merely filters out the IO pins that we are not using. It's returning the value `0x3F00` which is binary `0011 1111 0000 0000`. This gives us 5 IO pins in the place of the `1`'s which will eventually be `PB0`, `PB1`, `PB2`, `PB3`, `PB4` and `PB5`. Looking at the Arduino Uno Pinout that's the pins 8 to 13. Thus far, the calculation of `port_b` is: 
```c
0xFFFF & 0x3F00 >> SHIFT_PORT_B = 0x3F00 >> SHIFT_PORT_B
```
If we now look at the value `0x3F00` it didn't change because when &'ed with `0xFFFF` it's the same value. Remember that in binary `0x3F00` is `0011 1111 0000 0000`. We want to set the first 6 IO pins, hence the reason we used the `0x3F00` mask in the first place. That's why we need to shift these values to the right into `PB0` to `PB5`. Thus, `SHIFT_PORT_B` is simply the value 8 giving:

```c
0x3F00 >> 8 = 0011 1111 0000 00000 >> 8 = 0000 0000 0011 1111
```
You can now see how the first 6 values of this number will equate to `PB0` through `PB5`.

For `PORTC` and `PORTD` the idea is exactly the same. However for `PORTD` we don't need a right shift because the values are already in the right place due to the `PORT_D_MASK`. This is merely because we needed those pins on the Arduino board and this is how it was mapped. Otherwise `PORTD` calculation is exactly the same as `PORTB`. 

The calculation of `PORTC` is the same with one additional parameter, it has a XOR at the end. Remember that `PORTC` contains IO pins for planes and for columns? Due to this fact, we need to calculate which plane is currently going to be displayed and make that IO pin a `1`. That's the functionality of the `^` XOR operation at the end.

## Upload Code
### Arduino <img src="https://cdn.iconscout.com/icon/free/png-512/arduino-4-569256.png" alt="" width="30"/>
Do you wish to use the Arduino IDE? Read on.

#### Development Board
There will be no actual "Arduino Code" written. Keep in mind that "Arduino Code" is merely a C++ class. Most of the code that you write on an Arduino is usually merely C code anyway, so there isn't going to be a huge difference. If you plan to use your Arduino board, look at this board as a development board for the Atmega328. This board has a crystal, USB port and a programmer, among other things. So if you were going to buy a standalone Atmega328 instead, you would have to buy all these parts and connect them somehow. Luckily, you don't need that!

#### Bootloader
The Arduino board has another advantage, the Atmega328 on it comes with a bootloader. This means that there exists a tiny program on the chip that can easily upload code from your computer with a USB cable. It's not that easy with standalone chips. This is a very convenient thing that is going to be exploited in this project.

#### Arduino IDE
The cool thing about the bootloader and the IDE is that they are developed to work together. Just open the project in the IDE, choose your Arduino board and flash the code, it's _that_ simple.

### Atmel Studio <img src="https://www.it.unlv.edu/sites/default/files/styles/250_width/public/sites/default/files/assets/software/icons/atmel_studio.png?itok=Y_BrK5R2" alt="" width="20"/>
Do you wish to use Atmel Studio with or without an Arduino board? Read on.

#### Arduino Board
If you are using the Arduino board, the bootloader on the chip will be utilized for uploading and it works just as simply as the Arduino IDE.
TODO: Add how to set up Arduino upload.

#### Standalone Atmega328
If you don't have an Arduino board, you will need a programmer. Configure Atmel Studio according to the type of programmer you have, and upload the code.

## Download and Tools

### Code
The code can be downloaded from [Releases](https://github.com/mariugul/LED-Cube-Code/releases) or simply fork or download the repository.

### Tools
**[Arduino IDE](https://www.arduino.cc/en/main/software)**

**[Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7)**

## Help and Contributing
Check out the [Discord](https://discord.com/invite/ZgxjkC2) server if you need help with the code not working or if you have suggestions for improvement! The [YouTube]() channel has video tutorials to help out as well. (YouTube videos coming soon)

## Previous Version
The first version of the LED cube code was written entirely on Arduino. This code uses lots of nested `for()` and `while()` loops as well as `delay()`. It's simple and it works. The code, corresponding code generator and instructions can be found at [Instructables](https://www.instructables.com/id/LED-CUBE-CODE-4x4x4-Arduino/) <img src="https://logodix.com/logo/1584749.png" alt="" width="15"/> for anyone interested. Who wrote the Arduino code is not known to me, however I made the code generator application which is now deprecated to the newer [Cube 3D](https://github.com/mariugul/cube-3d).    

## License
This project is licensed under the MIT license and is open source. You are free to use this project as you wish as long as you credit the work. See the [LICENSE](LICENSE) file for details. I would highly appreciate if you contributed to the project that you share it so this can be a big open source project!

## Authors

<img src="https://lh3.googleusercontent.com/fqYJHtyzZzA4vacRzeJoB93QNvA5-mvR-8UB5oVLxdYDSTpfLp_KgYD4IqVGJUgFEJo" alt="" width="15"/> [Marius C. K. Gulbrandsen](https://www.linkedin.com/in/marius-c-k-gulbrandsen-963a69130/) 
