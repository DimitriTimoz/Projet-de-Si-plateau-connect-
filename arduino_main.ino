/******************************************************************
  Created with PROGRAMINO IDE for Arduino - 28.04.2019 16:14:49
  Project     :
  Libraries   :
  Author      :
  Description :
******************************************************************/



int OnCase[4][4]; // init table
int Score = 0;
int x;
int y;

void OnAllLed(int team) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; j++) {
      table[i][j] = 1;
    }
  }
}

int goToCenter[][] =
  [[
     [1, 1, 1, 1],
     [1, 0, 0, 1],
     [1, 0, 0, 1],
     [1, 1, 1, 1]
   ],
   [
     [0, 0, 0, 0],
     [0, 1, 1, 0],
     [0, 1, 1, 0],
     [0, 0, 0, 0],
   ]]

void animGoToCenter() {
  for (int i = 0; i < 2; i++)
  {
    for (int j = 1; j < 3; j++;) {
      Delay(1000 * 2);
      onCases(goToCenter[i], j )
    }
  }
}


//Set case according to score
void setCase() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; j++) {
      OnCase[i][j] = 0;
    }
  }
  x = (Score / 4);
  y = (Score % 4) - 1;

  // switch 0 to 3
  if ((x % 2) == 1)
  {
    if (y == 0) {
      y = 3;
    } else if (y == 1) {
      y = 2;
    } else if (y == 2) {
      y = 1;
    } else if (y == 3) {
      y = 0;
    }
    x = (Score / 4);
    OnCase[x][y] = 1;
  }
}

//read the data sheet
void onCases(int table[4][4], int team) {
  int caseNum = 0;
  Serial.println("");
  for (int i = 0; i < 4; ++i) {
    Serial.println("");
    for (int j = 0; j < 4; j++) {
      Serial.print(table[i][j]);
      ++caseNum;
      if (table[i][j] == 1 && team == 1) {
        digitalWrite(caseNum, 1);
      } if (table[i][j] == 1 && team == 2) {
        digitalWrite(caseNum + 16, 1);
      } if (table[i][j] == 0 && team == 2) {
        digitalWrite(caseNum + 16, 0);
      } else {
        digitalWrite(caseNum, 0);
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  for (int i = 1; i < 17; ++i)
  {
    Score = i;
    setCase();
    onCases(OnCase, 1);
  }

}

void loop()
{



}

