# Robotguide esp source
Sourcecode for the esp used by the robotguide to send and receive messages
to and from the robotguide arduino and the server.  

Currently the esp only forwards the instructions and responses and does not modify them in any way.

## Setup
1. Change the following in the code:
⋅⋅* Change the SSID name in "ssid".
⋅⋅* Fill in Wi-Fi password in "pass".
⋅⋅* Fill in the server IP address in "ip".

2. Connect the ESP8622 with the Arduino UNO
⋅⋅* Connect the UART cables (TX and RX).
⋅⋅* Use VIN to power the ESP8622 board.

3. Wait for the ESP to connect to the server. 
⋅⋅* ESP8622 LED will Blink fast when its connecting to Wi-Fi.
⋅⋅* ESP8622 LED will Blink slowly when connecting to the server.
⋅⋅* ESP8622 LED will stay on when its connected to the server and Wi-Fi.


## Possible future todo's
[] bake a cake...
(you can remove this section if not necessary)
