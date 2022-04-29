/**
 * Name: meArm gripper algorithm
 * Purpose: enable meArm robot to use the gripper.
 *
 * @author Diego Romeo
 * @version 1.0 14/04/2022
 */

#include <Servo.h>

int angle4;

Servo s4;

void setup()
{
    s4.attach(4);
}

void loop()
{
    s4.write(90);
}
