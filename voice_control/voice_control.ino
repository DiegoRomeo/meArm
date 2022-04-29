/**
 * Name: meArm voice control
 * Purpose: enable voice control for meArm robot.
 *
 * @author Diego Romeo
 * @version 1.0 24/04/2022
 */

#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;

int angle1;
int angle2;
int angle3;
int angle4;

const int BUFFER_SIZE = 100;
char buf[BUFFER_SIZE];

/**
 * Rotates a given servo motor by a given angle.
 * 
 * @param input A String containing the indicative number of the servo (1, 2, 3, 4)
 * and the angle to which it has to rotate.
 */
void voiceControl(String input)
{
  int servo = String(input.charAt(0)).toInt();
  int angle = input.substring(2).toInt();

  switch (servo)
  {
  case 1:
    s1.write(angle);
    break;
  case 2:
    s2.write(angle);
    break;
  case 3:
    s3.write(angle);
    break;
  case 4:
    s4.write(angle);
    break;
  default:
    break;
  }
}

/**
 * Get input from user.
 * 
 * @param message The message to display on the Serial Monitor.
 */
String getInput()
{ 
  while (Serial.available() == 0) {};
  String input = Serial.readStringUntil("\n");

  return input;
}

void setup() {
  Serial.begin(9600);
  
  s1.attach(10);
  s2.attach(9);
  s3.attach(5);
  s4.attach(4);
}

void loop() {
  String input = getInput();
  voiceControl(input);
}
