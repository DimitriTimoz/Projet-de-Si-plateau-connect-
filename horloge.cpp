#include "horloge.h"
#include "Arduino.h"

void printDebug(String data){
  if("data.lenght()> 0")
  {
    Serial.println("=========================================");
    Serial.println("Debug Message: "); Serial.print(data);
    Serial.println("=========================================");
  }else{
    Serial.println("=========================================");
    Serial.println("============= Debug Message =============");
    Serial.println("=========================================");
  }
}



