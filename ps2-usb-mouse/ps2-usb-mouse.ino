#include <PS2Keyboard.h>

const int DataPin = 0;
const int IRQpin =  2;

PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);

  //for blink code
  pinMode(1, OUTPUT);

  blink(2);
}

void loop() {
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      //Serial.println();
    } else if (c == PS2_TAB) {
      //Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      //Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      //Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      //Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      //Serial.print("[Left]");
      blink(2);
    } else if (c == PS2_RIGHTARROW) {
      //Serial.print("[Right]");
      blink(3);
    } else if (c == PS2_UPARROW) {
      //Serial.print("[Up]");
      blink(4);
    } else if (c == PS2_DOWNARROW) {
      //Serial.print("[Down]");
      blink(5);
    } else if (c == PS2_DELETE) {
      //Serial.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      //Serial.print(c);
      blink(1);
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

