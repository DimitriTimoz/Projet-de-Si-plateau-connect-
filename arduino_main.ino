/******************************************************************
   Created with PROGRAMINO IDE for Arduino - 28.04.2019 16:14:49
   Project     : Plateau connecté via hc 06 à l'application.
   Libraries   : SoftwareSerial.h
   Authors     : Egone and Dimitri
   Description :
******************************************************************/
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 2); // RX | TX


int    OnCase[4][4]; // init table
int    ScoreBleus[4][4];
int    ScoreRouges[4][4];
int _ScoreBleus = 0;
int _ScoreRouges = 0;
int    Score = 15;
int    x;
int    y;
String lastCommand;
int team;


/*
   SETUP
*/

void setup()
{
  Serial.begin(57600);
  bluetooth.begin(9600);
  Score = 0;
  setCase(Score);
  readTable(OnCase, 2);
}

/*
   LOOP
*/

void loop()
{
  testCommand(testReceiveCommand());
}


/*
   Data sheet
*/

int goToCenter[2][4][4] = {
  {
    { 1, 1, 1, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 1, 1, 1 }
  },
  {
    { 0, 0, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 }
  }
};

int chronoframes[2][4][4] = {
  {
    { 1, 0, 1, 0 },
    { 0, 1, 0, 1 },
    { 1, 0, 1, 0 },
    { 0, 1, 0, 1 }
  },
  {
    { 0, 1, 0, 1 },
    { 1, 0, 1, 0 },
    { 0, 1, 0, 1 },
    { 1, 0, 1, 0 }
  }
};

/*
   Command
*/

void sendCommand(String txt)
{
  String command = "/";

  command += txt;
}

void testCommand(String Command)
{
  delay(200);
  if (Command[0] == '/') {
    String settings[4];
    int j = 0;
    // split command
    for (int i = 0; i <= Command.length(); ++i) {
      if (' ' == Command[i]) {
        j++;
      } else {
        settings[j] += Command[i];
      }
    }

    //Test all commmands
    if (settings[0] == '/start')
    {
      StartGame();
    }
    else if (settings[0] == '/win')
    {
      if (settings[1] == "1") {
        OnAllLed(1);
      }
      else if (settings[1] == "2") {
        OnAllLed(2);
      }
    }
    else if (settings[0] ==  "/question")
    {
      Question();
    }
    else if (settings[0] == "/position")
    {
      _ScoreBleus = settings[1].toInt();
      _ScoreRouges = settings[2].toInt();
      AfficheScore(_ScoreBleus, _ScoreRouges);
    }
  }
}

String testReceiveCommand()
{
  String _command = "";
  while (bluetooth.available() > 0)
  {
    if (bluetooth.available() > 0)
    {
      char c = bluetooth.read();
      _command += c;
    }
  }
  return _command;
}

/*
   Commands
*/

void AfficheScore(int teamBleu, int teamRouge) {
  for (int i = 0; i <= 16; i++) {
    for (int j = 0; j <= 16; j++) {
      ScoreRouges[i][j];
    }
  }

  for (int i = 0; i <= 16; i++) {
    for (int j = 0; j <= 16; j++) {
      ScoreBleus[i][j];
    }
  }

  //generate x and y
  x = (teamBleu / 4);
  y = (teamBleu % 4);

  // switch 0 to 3
  if ((x % 2) == 1)
  {
    y = 3 - y;
  }
  ScoreBleus[x][y] = 1;

  x = (teamRouge / 4);
  y = (teamRouge % 4);

  // switch 0 to 3
  if ((x % 2) == 1)
  {
    y = 3 - y;
  }
  ScoreRouges[x][y] = 1;

  OffAllLed();
  readTable(ScoreBleus, 1);
  readTable(ScoreRouges, 1);
}

void StartGame() {
  bluetooth.print("Prêt");
}

void Question()
{
  long tpsTag = millis(); // init tag
  while (true)
  {
    for (int i = 0; i < 2; i++)
    {
      int j = 1;
      while ( j < 3)
      {
        if (delayNoFreeze(tpsTag, 500)) {
          tpsTag = millis();
          readTable(chronoframes[i], j);
          j++;
        }
        //Test if team buzze
        if (testBuzzeTeam() == 1) {
          bluetooth.print("/bleues");
          OnAllLed(1);
          return 0;
        } else if (testBuzzeTeam() == 2) {
          bluetooth.print("/rouges");
          OnAllLed(2);
          return 0;
        } else if (testReceiveCommand() == '/timeOut') {
          AfficheScore(_ScoreBleus, _ScoreRouges);
        }
      }
    }
  }
}


int testBuzzeTeam()
{
  bool haveNotBuzz = true;
  team = 0;

  if ((digitalRead(1) == LOW ) && (haveNotBuzz == true))
  {
    haveNotBuzz = false;
    team     = 1;
  }
  else if ((digitalRead(2) == LOW)  && (haveNotBuzz == true))
  {
    haveNotBuzz = false;
    team     = 2;
  }
  return 0;
}

/*
   Switch On led
*/

void OnAllLed(int team)
{
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; j++)
    {
      OnCase[i][j] = 1;
    }
  }
}

void OffAllLed() {
  for (int i = 10; i < 42; i++) {
    digitalWrite(i, 0);
  }
}

//read the data sheet
void readTable(int table[4][4], int team)
{
  int caseNum = 0;
  Serial.println("");
  for (int i = 0; i < 4; ++i)
  {
    Serial.println("");
    for (int j = 0; j < 4; j++)
    {
      Serial.print(table[i][j]);
      ++caseNum;
      if (table[i][j] == 1 && team == 1)
      {
        digitalWrite(caseNum + 10, 1);
      }
      if (table[i][j] == 1 && team == 2)
      {
        digitalWrite(caseNum + 26, 1);
      }
    }
  }
}
/*
   Animate
*/

void animGoToCenter()
{
  for (int i = 0; i < 2; i++)
  {
    for (int j = 1; j < 3; j++)
    {
      delay(1000 * 2);
      readTable(goToCenter[i], j);
    }
  }
}
/*
   Transform score to data sheet
*/
void clearAll() {
  for (int i = 0; i <= 16; i++) {
    for (int j = 0; j <= 16; j++) {
      OnCase[i][j];
    }
  }
}
void setCase(int score)
{
  clearAll();
  //generate x and y
  x = (score / 4);
  y = (score % 4);

  // switch 0 to 3
  if ((x % 2) == 1)
  {
    y = 3 - y;
  }
  OnCase[x][y] = 1;
}

String *readCommand(String command, char split) {
  int j = 0;
  String settings[4];
  for (int i = 0; i <= command.length(); ++i) {
    if (split == command[i]) {
      j++;
    } else {
      settings[j] += command[i];
    }
  }
  return settings;
}

bool delayNoFreeze(long tag, long time_) {
  if (tag + time_ < millis()) {
    return true;
  } else {
    return false;
  }
}

