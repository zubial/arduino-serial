/*
 Software serial interface

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 */
#include <SoftwareSerial.h>

// Set Pin used by Hardware serial
SoftwareSerial hwSerial(10, 11); // RX, TX

char incomingByte = "";
char outgoingByte = "";
bool incomingNewLine = true;
bool outgoingNewLine = true;

void setup() {

  // Open console Serial port
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect.
  }

  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");

  // Open hardware Serial port
  hwSerial.begin(115200);

  Serial.println("Started");
}

void loop() {
  if (hwSerial.available()) {
    outgoingByte = hwSerial.read();

    if (outgoingByte!=10 & outgoingByte!=13)
    {
      if (outgoingNewLine) {
        Serial.println("");
        Serial.print(" < ");
        outgoingNewLine = false;
      }
      Serial.print(outgoingByte);
      incomingNewLine = true;
    }
  }

  if (Serial.available()) {
    incomingByte = Serial.read();

    if (incomingByte!=10 & incomingByte!=13)
    {
      if (incomingNewLine) {
        Serial.println("");
        Serial.print(" > ");
        incomingNewLine = false;
      }
      Serial.print(incomingByte);
      outgoingNewLine = true;

      hwSerial.write(incomingByte);
    }
  }
}
