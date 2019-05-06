#include "MyCommands.h"
#include "Arduino.h"

void sendCommand(String txt)
{
  String command = "/";

  command += txt;
}

void testCommand(String Command)
{
  if (Command == "/start")
  {
    Serial.println("Start");
  }
  else if (Command == "/chrono")
  {
    Serial.println("Chrono");
  }
  else if (Command == "/win")
  {
    Serial.println("Win");
  }
  else if (Command == "/position")
  {
    Serial.println("Position");
  }
  else if (Command == "/question")
  {
    Serial.println("question");
  }
}

void testReceiveCommand()
{
  String command;
  byte   incomingByte;

  if (bluetooth.available())
  {
    //while (bluetooth.available())
   / {
    //  incomingByte = bluetooth.read();
    //  command     += char(incomingByte);
   // }
   // Serial.println(command);
   // lastCommand = command;
   // testCommand(command);
   Serial.write(bluetooth.read());
  }
  return 0;
}

/*
 * Commands
 */

void Question()
{
  while (true)
  {
    for (int i = 1; i <= 2; i++)
    {
      OnAllLed(i);
      delay(500);
      if (lastCommand == "/buzze1")
      {
        OnAllLed(1)
      }
      else if (lastCommand == "/buzze2")
      {
        OnAllLed(2)
      }
    }
  }
}

int testBuzzeTeam()
{
  bool haveBuzz = false;

  if (digitalRead(1) == LOW && haveBuzz != true)
  {
    haveBuzz = true;
    team     = 1;
  }
  else if (digitalRead(2) == && haveBuzz != true)
  {
    haveBuzz = true;
    team     = 2;
  }
  return team;
}

