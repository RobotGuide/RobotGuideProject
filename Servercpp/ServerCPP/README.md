# Server CPP

The server cpp exists of 3 projects.

The main project: ServerCPP is used to create the main project library. This can be used by any other project. It doesnt output a .exe file but a .lib

All subprojects use the static library produced by servercpp to create their own executable.



If you want to make an integration test, make a new project and properly link it with the main static library. This way you don't interfere with other projects, and are able to properly test your code.