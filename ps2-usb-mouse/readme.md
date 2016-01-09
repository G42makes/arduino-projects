#PS/2 - USB Mouse
##Keyboard Edition

This take input from a PS/2 keyboard and uses it to act as a USB mouse.

###Libraries
PS/2 Keyboard reading
https://www.pjrc.com/teensy/td_libs_PS2Keyboard.html

Emulating USB Mouse
https://github.com/adafruit/Adafruit-Trinket-USB

###Hardware
This project uses a Trinket from Adafruit for the main system. It could easily be built with just an ATTiny85 and some basic parts if you wish, I don't have those details. The keyboard must be a PS/2 compatible one in order to send the data that this system expects.

Look up a PS/2 connector diagram online or at the site of the library listed above. Connect as below:

| PS/2   | Trinket |
|--------|---------|
| Power  | 5V      |
| Ground | Gnd     |
| Clock  | #2      |
| Data   | #0      |

The Trinket takes care of the USB connector for us using pins #3 and #4, so no work needed there.

###Usage
Upload the code to your trinket. You should see a USB disconnect followed by a connect once it's online a moment later.
The following table has the keys and their actions listed. 

*Speed* is defaulted to 10 pixels

| Key     | Action                                                |
|---------|-------------------------------------------------------|
| [up]    | Move mouse up by *Speed*                              |
| [down]  | Move mouse down by *Speed*                            |
| [left]  | Move mouse left by *Speed*                            |
| [right] | Move mouse right by *Speed*                           |
| a       | Click left mouse button                               |
| s       | Click middle mouse button                             |
| d       | Click right mouse button                              |
| 0       | Set *Speed* to 1 pixel                                |
| 1       | Set *Speed* to 10 pixels (default)                    |
| [2-9]   | Set *Speed* to 10 X number pixels                     |
| [enter] | Toggle clicking left mouse button as fast as possible |

