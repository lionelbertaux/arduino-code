#include <IRLibAll.h>
#include <NewRemoteReceiver.h>

/* Code based on ShowReceivedCode.ino */

IRsend mySender;

void setup() {
    Serial.begin(115200);
    NewRemoteReceiver::init(0, 2, decode);
    Serial.print("Setup OK");
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  
}

void sendCommand(int level) {
  // Send command to IR
  // mySender.send(NEC,0xffe01f, 32);
 if (level == 0) {
    mySender.send(NEC,0xff609f, 32);
    Serial.print("OFF");
    digitalWrite(LED_BUILTIN, LOW);
 } else {
    mySender.send(NEC,0xffe01f, 32);  
    Serial.print("ON");
    digitalWrite(LED_BUILTIN, HIGH);
 }
  //delay(1000);
}

// Callback function is called only when a valid code is received.
void decode(NewRemoteCode receivedCode) {
  // Note: interrupts are disabled. You can re-enable them if needed.
  /*Serial.print("address: ");
  Serial.print(receivedCode.address);
  Serial.print(", groupBit:");
  Serial.print(receivedCode.groupBit);
  Serial.print(", unit:");
  Serial.print(receivedCode.unit);*/
  // Command is addressed to LED strip
  if (receivedCode.address==1) {
    if (receivedCode.groupBit==0) {
      if (receivedCode.unit==1) {
        // If dimLevel is sent, we use it. Otherwise we use the switchType
          switch (receivedCode.switchType) {
            case NewRemoteCode::off:
              Serial.print("off ");
              sendCommand(0);
              break;
            case NewRemoteCode::on:
              Serial.print("on ");
              sendCommand(16);
              break;
            case NewRemoteCode::dim:
            Serial.print("level ");
            Serial.print(receivedCode.dimLevel);
            sendCommand(receivedCode.dimLevel);
              break;
        }
        
      }
    }
  }
  Serial.println("");
}
