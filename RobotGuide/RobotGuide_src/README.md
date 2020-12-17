# Robotguide robot source
Sourcecode for the physical RobotGuide. The robotguide uses an Arduino Uno programmed with PlatformIO.

---

## Usage
The robot receives instructions via serial communication using the `Tx` and `Rx` pins. If an unknown command is given to the robot or the command was malformed during transit. The robot will send back a `NAVF\n` token via serial.

Commands have the following structure:  
`[COMMAND] [ARGUMENT]\n`  
The command and its argument are separated by a space character, The instructions themselves are separated by newline characters. The newline character is used to signify the end of a message.

Currently the robot has 4 commands:

#### FORN
Usage: `FORN [distance in millimeters]\n`  
Tells the robot to move forward a specified distance in millimeters. Once the robot has moved said distance it will send back a `NAVS\n` token via serial.

#### BACN
Usage: `BACN [distance in millimeters]\n`  
Tells the robot to move backward a specified distance in millimeters. Once the robot has moved said distance it will send back a `NAVS\n` token via serial.

#### TULN
Usage: `TULN [rotation in degrees]\n`  
Tells the robot to rotate a specified amount of degrees counter-clockwise. Once the robot has rotated said degrees it will send back a `NAVS\n` token via serial.

#### TURN
Usage: `TURN [rotation in degrees]\n`  
Tells the robot to rotate a specified amount of degrees clockwise. Once the robot has rotated said degrees it will send back a `NAVS\n` token via serial.

---

## Todo
[ ] implement new design from class diagram  
[ ] add PID controller to robot  
[ ] add unit tests  
[ ] create a static private method for calculating circumference in `movement.cpp`  
[ ] add a calibration constant variable to `movement` class  
[ ] replace macros in `main.cpp` with constants in header file
