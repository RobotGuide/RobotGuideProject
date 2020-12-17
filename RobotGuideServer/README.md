# RobotGuideServer Overview (deprecated)

## Content

- Product

- Functionality
- Limitations

## Product

The RobotGuideServer project was the first version of the Server application. But has been deprecated and finally abandoned, as C++ become a better choice. Because C++ offered the right features which C# didn't gave. We moved to the now called "servercpp" project.

## Functionality

The server application has the following functionality:

- Can connect to multiple clients
- Has basic application protocol supported

## Limitations

The server has currently some limitations such as:

- Doesn't support full robotguide application protocol
- Doesn't support reconnection
- Doesn't support pathfinding logic
- No obstacle resolvement algorithms (if obstacle has occured, find another path)

## Building RobotGuideServer

In order to build RobotGuideServer you need to do the following:

- Open visual studio solution
- Build solution