//From: https://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
#include <PS2Keyboard.h>

//From: https://github.com/adafruit/Adafruit-Trinket-USB
#include <TrinketMouse.h>

const int DataPin = 0;
const int IRQpin =  2;

PS2Keyboard keyboard;

//used for defining super click state using enter key
bool Click = false;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);

  TrinketMouse.begin();

  //for blink code
  pinMode(1, OUTPUT);
  blink(2);
}

void loop() {
  //click the mouse button if we have enable fast clicks
  //otherwise just report it not moving to keep USB happy
  //the library needs to implement: TrinketMouse.poll for non clicks really, the code is there, I might submit a patch.
  if (Click) {
    TrinketMouse.move(0, 0, 0, 1);
    TrinketMouse.move(0, 0, 0, 0);
  } else {
    TrinketMouse.move(0, 0, 0, 0);
  }
  
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      blink(1);
      // enable auto clicking
      Click = !Click;
    } else if (c == PS2_LEFTARROW) {
      blink(1);
      TrinketMouse.move(-10,0,0,0);
    } else if (c == PS2_RIGHTARROW) {
      blink(1);
      TrinketMouse.move(10,0,0,0);
    } else if (c == PS2_UPARROW) {
      blink(1);
      TrinketMouse.move(0,-10,0,0);
    } else if (c == PS2_DOWNARROW) {
      blink(1);
      TrinketMouse.move(0,10,0,0);

    // and use some keys as mouse buttons  
    } else if (c == 'a') {
      //press 'a', click left mouse button
      blink(1);
      TrinketMouse.move(0,0,0,1);
      TrinketMouse.move(0,0,0,0);
    } else if (c == 'd') {
      //press 'd' to click right mouse button
      blink(1);
      TrinketMouse.move(0,0,0,2);
      TrinketMouse.move(0,0,0,0);
    } else if (c == 's') {
      //press 's' to click mouse wheel
      blink(1);
      TrinketMouse.move(0,0,0,4);
      TrinketMouse.move(0,0,0,0);
    } else {
      
      // otherwise, just print all normal characters
      //Serial.print(c);
      blink(1);
      TrinketMouse.move(random(), random(), random(), random() & 0x07);
    }
  }
}

void blink( int c ) {
  for ( int i=c; i>0; i-- ) {
    digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(10);              // wait for a moment
    digitalWrite(1, LOW);    // turn the LED off by making the voltage LOW
    delay(10);              // wait for a moment
  }
}

