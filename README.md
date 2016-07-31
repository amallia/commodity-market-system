# Commodity Market System – CMS

[![Build Status](https://travis-ci.com/amallia/commodity-market-system.svg?token=2Cpy658AqNAqbjLFA4Z2&branch=master)](https://travis-ci.com/amallia/commodity-market-system)

**Antonio Mallia** *(me@antoniomallia.it)*

Project developed as part of the Bloomberg pre-class training.

Main task is to create an electronic platform for trading commodities contracts.
Implemented in C++ as a CLI program and then extended to accept communication over a TCP socket.




## Extensions

1. TCP socket and single connection only accepted
2. TCP socket and multiple connections accepted

Both the extensions have been implemented. For TCP Socket it has been used Boost.Asio library,for the multi-threading Boost.Thread.


## Design overview

Main function is defined in ```cms.cpp```, it reads program arguments and runs according to the selected input method.
It can be executed as a CLI program using stdin/stdout or over a TCP socket in both single and multi-threaded way.

Message parsing has been done using a Recursive Descendent (RD) parser.
Class Tokenizer splits the message and identifies the token types. Class Parser gets tokens and checks if it is corrected for the provided grammar.

*Dealers ID, Commodities and Commands are particular token types, they cannot have naming conflicts. This assumption has been made due to the fact that they have been presented in the grammar definition.*

Once the message has been parsed a Command object is returned. Command is the base type for several specialized command types, all of them implement an ```execute()``` method which is in charge of executing the command.
Executing a command means doing security checks over the provided message, e.g. verify that the dealer is the owner of the specified order in a Check command, and interacting with the order database.

Order database has been implemented as a map of IDs and Orders, managing the database is possible thought the ```orderRepository.cpp``` functions.
To avoid iterating over the whole orders database two indexes have been design to select orders for a given commodity or for the pair commodity-dealer.
This introduces an extra space cost, but it reduce the ```list``` cost from O(N) complexity to O(1).
Unfortunately, doing a LIST command means iterating over the list of results to correctly format them and this turns in a performance reduction since the complexity is in average still O(N) due to the limited number of commodities and dealers.

### External Libraries

- [Better Enums](https://github.com/aantron/better-enums)

    * Enum types generated at compile time.
    * Used for converting enums to and from strings to avoid maps or switch statements.


- [Boost](http://www.boost.org/)

    * Used macros with support for preprocessor metaprogramming to generate code.
    * Used format library for formatting arguments according to a format-string.
    * Used smart pointer library to make the project compatible with non-C++11 compilers.
    * Used algorithms library to operate on strings.
    * Used lexical_cast function template for supporting common conversions.
    * Boost.Asio to implement network extension.
    * Boost.Thread to implement multiple connections extension and locking features.
    * Boost.Test for unit testing.

    Project developed with Boost 1.60.0 (also tested with version 1.54)

### Tools

- [CMake](https://cmake.org/)

Project developed with CMake 3.3.2 (also tested with version 2.8)

- [GCC](https://gcc.gnu.org)

Project compiled using gcc 6.1.0 (also tested with version 4.8.4)


## Usage

### Build

```bash

git clone git@github.com:amallia/commodity-market-system.git
cd commodity-market-system
mkdir build
cd build
cmake ..
make

```

### Testing

```bash

ctest

```

### Execution


```bash
./cms base|ext1|ext2 <portNo>

```

If ``` base ``` option selected to terminate the execution of the program type ```q``` or ```quit``` and then hit return.
For ``` ext1 ``` and ``` ext2 ``` the program terminates after all TCP connections have been closed.

### Docker

The below command runs the program using the Docker image provided.

```bash
docker run --rm -it --name cms amallia/cms
```

This command starts a docker container with the needed Boost library installed and the code already compiled.

The default option is ```base```, if you want to run the extensions please add ``` -e "MODE=ext1"``` and   ``` -e "PORT=3000"```, moreover ```-p 3000:3000``` is needed to map Docker port.

```bash
docker run --rm -it -p 3000:3000 -e "MODE=ext1" -e "PORT=3000" --name cms amallia/cms
```

## Continuous Integration

Continuous Integration is done using Travis-CI, configuration is specified in ``` .travis.yml ``` file.
