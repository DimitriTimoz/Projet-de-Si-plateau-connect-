#include "horloge.h"
#include "Arduino.h"

void printDebug(String data) {
  Serial.println("");
  if (sizeof(data) > 0)
  {
    Serial.println("=========================================");
    Serial.println("Debug Message: "); Serial.print(data);
    Serial.println("=========================================");
  } else {
    Serial.println("=========================================");
    Serial.println("============= Debug Message =============");
    Serial.println("=========================================");
  }
}

void testCommand(String Command) {
  if ( Command == "#Start") {
    Serial.println("#Start");
  } else if ( Command == "#Chrono") {
    Serial.println("#Chrono");
  } else if ( Command == "#Buzze") {
    Serial.println("#Buzze");
  } else if ( Command == "#Win") {
    Serial.println("#Win");
  } else if ( Command == "#Position") {
    Serial.println("#Position");
  }
}


bool testIfNewCommand() {
  bool newCommand = false;
  return newCommand;
}

