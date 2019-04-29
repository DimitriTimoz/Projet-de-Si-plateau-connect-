/******************************************************************
  Created with PROGRAMINO IDE for Arduino - 28.04.2019 16:14:49
  Project     : Plateau connecté via hc 05 à l'application.
  Libraries   :
  Authors     : Egone and Dimitri
  Description :
******************************************************************/
#include <SoftwareSerial.h>
#include "horloge.h"

SoftwareSerial bluetooth(2, 3); // RX | TX


int OnCase[4][4]; // init table
int Score = 0;
int x;
int y;

String command = "";

void OnAllLed(int team) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; j++) {
      OnCase[i][j] = 1;
    }
  }
}

int goToCenter[2][4][4] = {
  {
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1}
  },
  {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
  }
};

void animGoToCenter() {
  for (int i = 0; i < 2; i++)
  {
    for (int j = 1; j < 3; j++) {
      delay(1000 * 2);
      readTable(goToCenter[i], j );
    }
  }
}


//Set case according to score
void setCase(int data) {
  //clear
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; j++) {
      OnCase[i][j] = 0;
    }
  }
  //generate x and y
  x = (data / 4);
  y = (data % 4);

  // switch 0 to 3
  if ((x % 2) == 1)
  {
    y = 3 - y;
  }
  OnCase[x][y] = 1;
}

//read the data sheet
void readTable(int table[4][4], int team) {
  int caseNum = 0;
  Serial.println("");
  for (int i = 0; i < 4; ++i) {
    Serial.println("");
    for (int j = 0; j < 4; j++) {
      Serial.print(table[i][j]);
      ++caseNum;
      if (table[i][j] == 1 && team == 1) {
        digitalWrite(caseNum + 2, 1);
      } if (table[i][j] == 1 && team == 2) {
        digitalWrite(caseNum + 18, 1);
      } if (table[i][j] == 0 && team == 2) {
        digitalWrite(caseNum + 18, 0);
      } else {
        digitalWrite(caseNum +2, 0);
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  for (int i = 1; i < 17; ++i)
  {
    printDebug("");
    Score = i;
    setCase(Score);
    readTable(OnCase, 2);
  }

}

void loop()
{
  if (bluetooth.available())
  {
    Serial.write(bluetooth.read());
  }
  while (Serial.available())
  {
    delay(3);
    bluetooth.write(Serial.read());
  }
}




