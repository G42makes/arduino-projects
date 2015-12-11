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
#define PIN             2
// And how many pixels we are driving. Probably > 110, as we can drive that many on the existing NeoPixel library
#define NUMPIXELS       3

//A lot of timing understanding comes from: https://cpldcpu.wordpress.com/2014/01/14/light_ws2812-library-v2-0-part-i-understanding-the-ws2812/
//And a lot of understanding of WS2812 bitbanging from: http://www.instructables.com/id/Bitbanging-step-by-step-Arduino-control-of-WS2811-/?ALLSTEPS

//some setup for static value I may use later(ripped from adafruit library)
volatile uint8_t  *port;         // Output PORT register
uint8_t  pinMask;                // Output PORT bitmask

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  //    Also from: https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/simple/simple.ino
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

//For the first test, let's just light up one pixel with something.
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  port    = portOutputRegister(digitalPinToPort(PIN));
  pinMask = digitalPinToBitMask(PIN);
  noInterrupts(); // Need 100% focus on instruction timing
  
  volatile uint16_t
    //i   = numBytes; // Loop counter
    i = 8;
  volatile uint8_t
    //*ptr = pixels,   // Pointer to next byte
    //b   = *ptr++,   // Current byte value
    b = 255,
    hi,             // PORT w/output bit set high
    lo;             // PORT w/output bit set low

    // 20 inst. clocks per bit: HHHHHxxxxxxxxLLLLLLL
    // ST instructions:         ^   ^        ^       (T=0,5,13)

    volatile uint8_t next, bit;

    hi   = *port |  pinMask;
    lo   = *port & ~pinMask;
    next = lo;
    bit  = 8;

    asm volatile(
     "head20:"                   "\n\t" // Clk  Pseudocode    (T =  0)
      "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
      "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
      "mov  %[next], %[hi]"      "\n\t" // 0-1   next = hi    (T =  4)
      "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
      "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
      "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
      "breq nextbyte20"          "\n\t" // 1-2  if(bit == 0) (from dec above)
      "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
      "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
      "nop"                      "\n\t" // 1    nop           (T = 13)
      "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
      "nop"                      "\n\t" // 1    nop           (T = 16)
      "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
      "rjmp head20"              "\n\t" // 2    -> head20 (next bit out)
     "nextbyte20:"               "\n\t" //                    (T = 10)
      "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
      //"ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
        "rjmp .+0"                 "\n\t" // 2    nop nop
      "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
      "nop"                      "\n\t" // 1    nop           (T = 16)
      "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
       "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
      : [port]  "+e" (port),
        [byte]  "+r" (b),
        [bit]   "+r" (bit),
        [next]  "+r" (next),
        [count] "+w" (i)
      //: [ptr]    "e" (ptr),
      : [hi]     "r" (hi),
        [lo]     "r" (lo));
    
    interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:

}
