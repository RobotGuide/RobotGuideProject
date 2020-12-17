# Servercpp Overview

## Content

- Product
- Functionality
- Limitations
- Building Servercpp
- Contributing

## Product

The servercpp project is used as server application for the robotguide. It is responsible for the communication between robotguides and users. Users can connect with the server and ask for a path. The server finds this path and finds a suitable robot to guide the user.

## Functionality

The server application has the following functionality:

- Path finding algorithms
- Basic application protocol
- TCP transport protocol support
- Multi robot connection support

## Limitations

The server has currently some limitations such as:

- Doesn't support full robotguide application protocol
- Limited set of path finding algorithms
- No obstacle resolvement algorithms (if obstacle has occured, find another path)

## Building Servercpp

In order to compile any project in Servercpp solution, you should use the x86 Debug configuration. This configuration is pre-set for correctly compiling the source code and tests.

### Release build

In order to build the server you need to do the following:

- Open Servercpp solution

- Build the main server library project
- Build the main server executable project

### Test builds

There are also a lot of test builds one can build. These are in projects that start with the name "test", or have "test" in their name.

In order to build these test executables you should do the following:

- Open Servercpp solution

- Build the main server library project
- Build the desired test build project

Note: These test builds only test 1 feature.

## Contributing

If you want to extend or contribute to the servercpp project you need to know the following:

- The servercpp project was made in C++17. 

- The servercpp also uses a specific directory structure.

  It uses an include folder for all the header files, and uses a lib folder for all source files.