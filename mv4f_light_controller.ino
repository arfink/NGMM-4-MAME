/*
  Reading a serial ASCII-encoded string from MAME + Python to drive LEDs for 4 slot lights in Neo Geo MVS.
 
 */

// pins for the LEDs:
const int slot1Pin = 2;
const int slot2Pin = 3;
const int slot3Pin = 4;
const int slot4Pin = 5;

// pins for shift registers
const int SER=8;
const int LATCH=9;
const int CLK=10;
// sequencer test data
int seq []= {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
// variables for last digit 1 and 2 values
int digit1current = 63;
int digit2current = 63;

void setup() {
  // initialize serial:
  Serial.begin(57600);
  // make the pins outputs:
  pinMode(slot1Pin, OUTPUT);
  pinMode(slot2Pin, OUTPUT);
  pinMode(slot3Pin, OUTPUT);
  pinMode(slot4Pin, OUTPUT);
  pinMode (SER, OUTPUT);
  pinMode (LATCH, OUTPUT);
  pinMode (CLK, OUTPUT);
  // reset the 7 segment displays
  digitalWrite (LATCH, LOW);
  shiftOut (SER, CLK, MSBFIRST, digit1current);
  shiftOut (SER, CLK, MSBFIRST, digit2current);
  digitalWrite (LATCH, HIGH);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int digitselect = Serial.parseInt();
    // do it again:
    int digitvalue = Serial.parseInt();

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {
      // read the digit selector code and value, encoded in 7-segment code, then switch lights on and off
      if (digitselect==1) {
        digit1current = digitvalue;
        }
      if (digitselect==2) {
        digit2current = digitvalue;
        }
      if (digitselect==0) {
        if (digitvalue==63) {
          digitalWrite(slot1Pin, LOW);
          digitalWrite(slot2Pin, LOW);
          digitalWrite(slot3Pin, LOW);
          digitalWrite(slot4Pin, LOW);
          }        
        if (digitvalue==6) {
          digitalWrite(slot1Pin, HIGH);
          digitalWrite(slot2Pin, LOW);
          digitalWrite(slot3Pin, LOW);
          digitalWrite(slot4Pin, LOW);
          }
        if (digitvalue==91) {
          digitalWrite(slot1Pin, LOW);
          digitalWrite(slot2Pin, HIGH);
          digitalWrite(slot3Pin, LOW);
          digitalWrite(slot4Pin, LOW);
          }
        if (digitvalue==79) {
          digitalWrite(slot1Pin, LOW);
          digitalWrite(slot2Pin, LOW);
          digitalWrite(slot3Pin, HIGH);
          digitalWrite(slot4Pin, LOW);
          }
        if (digitvalue==102) {
          digitalWrite(slot1Pin, LOW);
          digitalWrite(slot2Pin, LOW);
          digitalWrite(slot3Pin, LOW);
          digitalWrite(slot4Pin, HIGH);
          }

        }
    
      // output digits to the 7 segment displays
      digitalWrite (LATCH, LOW);
      shiftOut (SER, CLK, MSBFIRST, digit1current);
      shiftOut (SER, CLK, MSBFIRST, digit2current);
      digitalWrite (LATCH, HIGH);
      
      // print the two numbers to serial port:
      Serial.print(digitselect);
      Serial.println(digitvalue);

    }
  }
}
