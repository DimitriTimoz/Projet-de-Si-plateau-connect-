#include "horloge.h"
#include "Arduino.h"

void printDebug(String data){
  Serial.println("");
  if(sizeof(data)> 0)
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



