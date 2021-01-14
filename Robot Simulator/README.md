# Robot Simulator
Source code for the robot guide simulator.  

This simulator is primarily used in combination with the server for testing communication and protocols. It was also used to decouple the development of the server and the physical robot so that both could be developed independently.

The simulator was developed with the Unity game engine using version `2019.4.11f`

## Running the simulator
1) Make sure Unity is installed, this can be done from [this link](https://unity3d.com/get-unity/download)
2) Launch the project by opening it via the unity launcher, or alternatively opening the scenefile `Assets/_Scenes/SampleScene.unity` directly.
3) Once the editor has been opened you can either play the scene or build it into an excecutable
4) Start up the server. For instructions on how to do this look at the documentation found in the `ServerCpp README file`.
5) In the scene enter `3030` in the `Port` field, and fill in the server's ip-adress in the `Server Ip` field.
6) Click connect, the simulator will give a message if it has successfully connected.
7) You can now send commands to the robot simulator via the server.

if you want to connect as user you can use `3031` in the `Port`. This allows you to request a route for a different simulator.

The send button allows you to send a message dirrectly to the server. This is the case for both a robot and a user.
