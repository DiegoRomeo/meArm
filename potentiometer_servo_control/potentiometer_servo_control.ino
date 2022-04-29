/**
 * Name: meArm potentiometer servo control
 * Purpose: enable potentiometer servo control for meArm robot.
 *
 * @author Diego Romeo
 * @version 1.0 14/04/2022
 */

#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;  

int potPin1 = 0; 
int potPin2 = 1; 
int potPin3 = 2;
int potPin4 = 3;

int angle1;
int angle2;
int angle3;
int angle4;    

void setup() {
  s1.attach(10);
  s2.attach(9);
  s3.attach(5);
  s4.attach(4);
}

void loop() {
  angle1 = analogRead(potPin1);
  angle1 = map(angle1, 0, 1023, 0, 180);
  
  angle2 = analogRead(potPin2);            
  angle2 = map(angle2, 0, 1023, 0, 180); 
  
  angle3 = analogRead(potPin3);            
  angle3 = map(angle3, 0, 1023, 140, 180);

  angle4 = analogRead(potPin4);
  angle4 = map(angle3, 0, 1023, 0, 180);
  
  s1.write(angle1);
  s2.write(angle2);
  s3.write(angle3);
  s4.write(angle4);
                 
  delay(50);
}
