/**
 * Name: meArm forward kinematics
 * Purpose: enable forward kinematics for meArm robot.
 *
 * @author Diego Romeo
 * @version 1.0 14/04/2022
 */

#include <Servo.h>

int angle1;
int angle2;
int angle3;

Servo s1;
Servo s2;
Servo s3;

const int BUFFER_SIZE = 100;
char buf[BUFFER_SIZE];

/**
 * Rotates the servo motors by the given angles.
 * 
 * @param angle1 The angle by which the servo s1 is rotated.
 * @param angle2 The angle by which the servo s2 is rotated.
 * @param angle3 The angle by which the servo s3 is rotated.
 */
void ForwardKinematics(int angle1, int angle2, int angle3)
{
  s1.write(angle1);
  s2.write(angle2);
  s3.write(angle3);
  delay(50);
}

/**
 * Get input from user.
 * 
 * @param message The message to display on the Serial Monitor.
 */
int getInput(String message)
{
  String data = "";

  Serial.println(message);
  
  while (Serial.available() == 0) {};
  int rlen = Serial.readBytesUntil('\n', buf, BUFFER_SIZE);

  for(int i = 0; i < rlen; i++)
  {
    data += buf[i];
  }

  int input = data.toInt();

  return input;
}

void setup() {
  Serial.begin(9600);
  
  s1.attach(10);
  s2.attach(9);
  s3.attach(5);

  s1.write(90);
  s2.write(20);
  s3.write(150);
}

void loop() {  
  angle1 = getInput("Set the angle for s1 servo");
  
  angle2 = getInput("Set the angle for s2 servo");
  
  thirdAngle:
  angle3 = getInput("Set the angle for s3 servo. It must be between 140 and 180.");
  
  if (not(angle3 >= 140 && angle3 <= 180)) {
    Serial.println("Invalid angle!");
    goto thirdAngle;
  }
  
  ForwardKinematics(angle1, angle2, angle3);
}
