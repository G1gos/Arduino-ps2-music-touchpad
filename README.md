# Arduino-ps2-music-touchpad
Arduino project with laptop's touchpad
![In case](https://user-images.githubusercontent.com/107487372/173910013-def7c9c2-3631-4de0-a0e0-675cfd504d5a.png)

# Introduction
Music sensor touchpad is a first step to create an analog of Matt's Mellamy kaoss pad. Total cost of this project doesn't exceed 50$.

# Description of functions and supporting devices.

1. Main device is a laptop's touchpad (Synaptics 920-000436-01 for example) that will be using for changing sounds.
2. Dccduino UNO R3 (another version of Arduino).
3. LCD display for showing current key.
4. TTP226 touch sensor for changing key.
5. Dynamic output (jack-jack cabel)
Finally, a person using the touchpad and getting a melody on the dynamic. 

# Construction

![Construction](https://user-images.githubusercontent.com/107487372/174485287-cefa62ce-35fa-40b2-aa53-929356fae59a.png)

In the touchpad it needs to find 4 contacts: DATA, CLOCK, +5V and GND.
Digital ports are for TTP226 outs and DATA, CLOCK touchpad. Analog ports are for LCD display outs.

# Algorithm 

Touchpad can register only relative changes. It saves a first touch like 0:0 in X/Y system and then changes the value of them. Using COM-port you can see how it works. 

![COM](https://user-images.githubusercontent.com/107487372/174487031-d63d1be7-afb2-4aa9-8add-381b3cbbd5d9.png)

The third column shows that the movement goes in left side.

So X-movement will be change a note in one octave (I just created a massive with notes that consist in pentatonic scale). 
Y-movement sends the current note in next or the previous octave (*2, *4, /2, /4 of current note's value)
