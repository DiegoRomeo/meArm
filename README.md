# meArm
![meArm](https://github.com/DiegoRomeo/meArm/blob/main/maArm1.jpeg?raw=true)
A set of programs for meArm robot arm.

## Introduction
The meArm robot is a famous open source robotic arm with 4 degrees of freedom.  

It's widely diffused as there are more than 10,000 prototypes around the world and it's mainly used for educative purposes.

The purpose of this repository is to share Arduino sketches and Python scripts for meArm.
## Usage
- [Dance](#dance)
- [Forward Kinematics](#forward-kinematics)
- [Gripper](#gripper)
- [Inverse Kinematics](#inverse-kinematics)
- [Potentiometer Servo Control](#potentiometer-servo-control)
- [Voice Control](#voice-control)

### Dance
Upload the dance.ino sketch to your ArduinoUno board.  
After this you can run the python file named "dance.py" which requires as argument the path to the song the robot has to dance.  
To run the python script open your terminal and run the following command:  
```
$ python dance.py <PATH TO SONG>
```
### Forward Kinematics
Upload the forward_kinematics.ino sketch to your ArduinoUno board.  
After this you can open the Serial Monitor through the Arduino IDE and input the values of the angles at which the servo motors will be rotated.
### Gripper
### Inverse Kinematics
Currently not working.
### Potentiometer Servo Control
Upload the potentiometer_servo_control.ino to your ArduinoUno board.  
After this you can control the robot by rotating the potentiometers.
### Voice Control
Upload the voice_control.ino sketch to your ArduinoUno board. 
After this you can run the file named "voice_control.py" to control the robot using your voice.  
To run the python script open your terminal and run the following command:  
```
$ python voice_control.py
```
The instruction must contain a command of the type:
```
<WORD1> <INTEGER1> <WORD2> <INTEGER2>
```
Where:
- WORD1 is a string containing only letters.
- INTEGER1 is an integer value in the range [1, 4], indicating the servo to move: each servo has an indicative number.
- WORD2 is a string containing only letters.
- INTEGER2 is an integer value in the range [140, 180] for servo 3 while for the others it can be in the range [0, 180]. It indicates the value of the angle (in degrees) at which the sevo has to be rotated.  

Example:
```
MOVE SERVO 1 AT 30 DEGREES
```
The instruction above contains the command values in the order specified before.
```
Project exhibited at RomeCup 2022
```