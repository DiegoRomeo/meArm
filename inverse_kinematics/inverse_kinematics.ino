/**
 * Name: meArm forward kinematics
 * Purpose: enable inverse kinematics for meArm robot.
 *
 * @author Diego Romeo
 * @version 1.0 17/04/2022
 */

#include <Servo.h>
#include <string.h>
#include <math.h>

#define D1 75
#define D2 82
#define H1 55
#define L0 5
#define L1 15.1
#define L2 75
#define L3 80
#define L30 35
#define L31 44
#define L4 82
#define L5 70
#define D5 5

const int BUFFER_SIZE = 100;
char buf[BUFFER_SIZE];

Servo s1; 
Servo s2; 
Servo s3;

/**
 * Converts an angle from radians to degrees.
 * 
 * @param radians The angle to convert.
 */
float toDegrees(float radians)
{
  float deg = (180*radians) / M_PI;
  return deg;
}

/**
 * Calculates the angles of the servo motors given a position to reach.
 * Then it rotates the motors.
 * 
 * @param x The x coordinate of the point to reach.
 * @param y The y coordinate of the point to reach.
 * @param z The z coordinate of the point to reach.
 */
void inverseKinematics(float x, float y, float z)
{
  int angle1;
  int angle2;
  int angle3;

  angle1 = atanf((x - L0) / (-y)) + asinf(D5 / sqrtf(pow((pow(x, 2) - L0), 2) + pow(y, 2)));
  angle1 = toDegrees(angle1);

  float r = sqrtf(pow(x-72, 2) + pow(y+15, 2)) - L1;
  float Z_e = z + 10 - H1;

  float alfa = atanf(Z_e / r);
  float s = sqrtf(pow(r, 2) + pow(Z_e, 2));
  
  float gamma = acosf((pow(L2, 2) + pow(L3, 2) - pow(s, 2)) / (2*L2*L3));
  float beta = acosf((pow(s, 2) + pow(L2, 2) - pow(L3, 2)) / (2*s*L2));

  angle2 = round(toDegrees(M_PI - alfa - beta));

  float q30 = M_PI - gamma;

  float e = sqrtf(pow(L30, 2) + pow(L2, 2) -2*L30*L2*cosf(q30));

  float psi = asinf((L30*sinf(q30)) / e);

  float phi = acosf((pow(e, 2) + pow(L31, 2) - pow(L4, 2)) / (2*e*L31));

  angle3 = round(toDegrees(psi + phi + M_PI/2 - angle2));
  angle3 = map(angle3, 0, 50, 140, 180);

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
float getInput(String message)
{
  String data = "";

  Serial.println(message);
  
  while (Serial.available() == 0) {};
  int rlen = Serial.readBytesUntil('\n', buf, BUFFER_SIZE);

  for(int i = 0; i < rlen; i++)
  {
    data += buf[i];
  }

  float input = data.toFloat();

  return input;
}

void setup() {
  s1.attach(10);
  s2.attach(9);
  s3.attach(5);
}

void loop() {
  Serial.begin(9600);

  float x = getInput("Insert the x coordinate of the target");
  float y = getInput("Insert the y coordinate of the target");
  float z = getInput("Insert the z coordinate of the target");

  inverseKinematics(x, y, z);
}