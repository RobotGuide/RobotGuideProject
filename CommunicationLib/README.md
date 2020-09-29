# CommunicationLib

## Purpose

- Enable communication between subsystems
- Handle communication between subsystems
- Enable communication through specific communication protocols
- Handle errors encountered based of communication protocols used
- Format data
- Filter data

More information can be found in the design document.

## Components

- ComLib
- ComLibDLL

Both components are developed in c++. But c# systems need to use the ComLibDLL to use the library, and c++ systems can use the standard static library.

The ComLibDLL is just a wrapper around the original static library.





Made by Thimo Böhmer. For questions about the module ask me in person or through mail.