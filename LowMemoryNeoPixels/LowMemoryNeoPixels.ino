// Where we try to not use memory in order to do more...
// This code runs either on a Adafruit Trinket(not pro) or a bare ATTiny85, set to 16MHz internal clock
//  See: https://learn.adafruit.com/introducing-trinket/16mhz-vs-8mhz-clock for info on 16MHz config
//  And according to that page we should include the following:
#include <avr/power.h>
//
// Let's set some values
//    Note that the first two here are basically copied from the NeoPixel Example, and other areas will be from there too.
//    https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/simple/simple.ino
// First up, what pin are we connected to
#define PIN             0
// And how many pixels we are driving. Probably > 110, as we can drive that many on the existing NeoPixel library
#define NUMPIXELS       3

//A lot of timing understanding comes from: https://cpldcpu.wordpress.com/2014/01/14/light_ws2812-library-v2-0-part-i-understanding-the-ws2812/
//And a lot of understanding of WS2812 bitbanging from: http://www.instructables.com/id/Bitbanging-step-by-step-Arduino-control-of-WS2811-/?ALLSTEPS

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  //    Also from: https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/simple/simple.ino
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

}

void loop() {
  // put your main code here, to run repeatedly:

}
