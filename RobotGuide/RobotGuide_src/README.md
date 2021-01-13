# Robotguide robot source
Sourcecode for the physical RobotGuide. The robotguide uses an Arduino Uno programmed with PlatformIO.

<div align="center">
<img src="images/robotguide.jpg" alt="Robot guide" width="50%" height="50%">
</div>

## Parts list
The robot was assembled using the following parts:
* [L298N motor driver](https://www.tinytronics.nl/shop/nl/robotica/motoren/motoraansturingen/l298n-bipolaire-stappenmotor-en-dc-motor-motoraansturing) x1
* [Circular robot kit from TinyTronics](https://www.tinytronics.nl/shop/nl/robotica/auto-kit-zelfbouw-rond) x2
* [Dc motor with 120:1 gearbox fomr TinyTronics](https://www.tinytronics.nl/shop/nl/robotica/reservemotor-auto-kit-zelfbouw-120:1) x2
* [B83609 Optical encoder](https://www.dx.com/p/hc-020k-double-speed-measuring-module-w-photoelectric-encoders-black-green-2-pcs-2027855.html) x2
* [400 point breadboard](https://www.tinytronics.nl/shop/nl/prototyping/breadboards/breadboard-400-points) x1
* [8x AA battery holder from TinyTronics](https://www.tinytronics.nl/shop/nl/batterij-en-accu/batterijhouders/8x-aa-batterij-houder-met-losse-draden) x1
* [8x eneloop 1.2v 750mAh AAA batteries](https://www.tinytronics.nl/shop/nl/batterij-en-accu/aaa/eneloop-oplaadbare-batterij-4x-aaa-750mah)
* 2.3 nanofarad capacitor x2 (though something similar to that range will probably also work)
* Arduino Uno mounting plate (optional but quite helpful)

(Note, you might need to use some bearings when mounting the motors to the chassis to get the right fitting, else the rotary encoders might not fit properly)

---

## Powering the robot
During this project the robot was mainly powered via 8 rechargable 1.2v 750mAh AAA batteries. Connected in series these gave 9.6v and 750mAh. When using a different power setup the following 2 points must be kept in mind:

The L298N motor driver is a very old model which is designed for much higher current. Because of this the L298N driver has a voltage drop of about 2.0v.

Currently, the code controlling the motordriver has a hardcoded motor speed to prevent
saturating and damaging the dc motors. When the voltage of the power source is change this speed must be changed manually to prevent damaging the motors.

An alternative to this setup would be to use a LiPo battery, which is able to supply the required current with a much lower voltage.

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

## Class diagram

<img src="images/classdiagram.png" alt="Class diagram">

---

## Todo
[x] implement new design from class diagram  
[x] add PID controller to robot  
[ ] add unit tests  
[x] create a static private method for calculating circumference in `movement.cpp`  
[ ] add a calibration constant variable to `movement` class  
[x] replace macros in `main.cpp` with constants in header file  
[ ] create circuit diagram  
[ ] replace power source with LiPo battery
