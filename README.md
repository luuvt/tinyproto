
![Tiny Protocol](.travis/tinylogo.svg)<br>
[![Build Status](https://travis-ci.com/lexus2k/tinyproto.svg?branch=master)](https://travis-ci.com/lexus2k/tinyproto)
[![Coverage Status](https://coveralls.io/repos/github/lexus2k/tinyproto/badge.svg?branch=master)](https://coveralls.io/github/lexus2k/tinyproto?branch=master)
[![Documentation](https://codedocs.xyz/lexus2k/tinyproto.svg)](https://codedocs.xyz/lexus2k/tinyproto/)

[tocstart]: # (toc start)

  * [Introduction](#introduction)
  * [Key Features](#key-features)
  * [Supported platforms](#supported-platforms)
  * [Easy to use](#easy-to-use)
  * [Setting up](#setting-up)
  * [How to buid](#how-to-build)
  * [Using tiny_loopback tool](#using-tiny_loopback-tool)
  * [License](#license)

[tocend]: # (toc end)

## Introduction

If you want to get stable code, please, refer to [stable branch](https://github.com/lexus2k/tinyproto/tree/stable).
HD (half duplex) protocol is removed from this version. If you need it, please refer to stable branch.

Tiny Protocol is layer 2 protocol. It is intended to be used for the systems with low resources.
It is also can be compiled for desktop Linux system, and it can be built it for Windows.
Using this library you can easy implement data transfer between 2 microcontrollers or between microcontroller and pc via UART, SPI,
I2C or any other communication channels.
You don't need to think about data synchronization between points. The library use no dynamic allocation of memory.
TinyProto is based on RFC 1662, it implements the following frames:
 * U-frames (SABM, UA)
 * S-frames (REJ, RR)
 * I-frames

## Key Features

Protocols, implemented by library:
 * Hot plug/unplug support
 * hdlc framing (hdlc_ll_xxxx, hdlc_xxxx API)
 * light (tiny_light_xxxx API, simplest API to use, doesn't support confirmation)
 * full-duplex (tiny_fd_xxxx true RFC 1662 implementation, supports confirmation, frames retransmissions)

Main features:
 * Error detection (low level, high level hdlc and full duplex (fd) protocols)
   * Simple 8-bit checksum (sum of bytes)
   * FCS16 (CCITT-16)
   * FCS32 (CCITT-32)
 * Frames of maximum 32K or 2G size (payload limit depends on platform).
 * Low SRAM consumption (starts at 50 bytes).
 * Low Flash consumption (starts at 1KiB, features can be disabled and enabled at compilation time)
 * No dynamic memory allocation!
 * Serial loopback tool for debug purposes and performance testing

## Supported platforms

 * Any platform, where C/C++ compiler is available (C99, C++11)

## Easy to use

Usage of light Tiny Protocol in C++ can look like this:
```.cpp
Tiny::ProtoLight  proto;
Tiny::Packet<256> packet;
...
    if (Serial.available()) {
        int len = proto.read( packet );
        if (len > 0) {
            /* Send message back */
            proto.write( packet );
        }
    }
```

Example of using full duplex Tiny Protocol in C++ is a little bit bigger, but it is still simple:
```.cpp
Tiny::ProtoFd<FD_MIN_BUF_SIZE(64,4)>  proto;

void onReceive(Tiny::IPacket &pkt) {
    // Process message here, you can do with the message, what you need
    // Let's send it back to the sender ;)
    if ( proto.write(pkt) == TINY_ERR_TIMEOUT ) {
        // Do what you need to do if looping back failed on timeout.
        // But never use blocking operations inside callback
    }
}
...
// Here we say FD protocol object, which callback to call once new msg is received
proto.setReceiveCallback( onReceive );
...
void loop() {
    if (Serial.available()) {
        uint8_t byte = Serial.read();
        proto.run_rx( &byte, 1 ); // run FD protocol parser to process data received from the channel
    }
    uint8_t byte;
    if ( proto.run_tx( &byte, 1 ) == 1 ) // FD protocol fills buffer with data, we need to send to the channel
    {
        while ( Serial.write( byte ) == 0 ); // Just send the data
    }
}
```

## How to build

### Linux
```.txt
make
# === OR ===
mkdir build
cd build
cmake -DEXAMPLES=ON ..
make
```

### Windows
```.txt
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -DEXAMPLES=ON ..
```

## Setting up

 * Arduino Option 1 (with docs and tools)
   * Download source from https://github.com/lexus2k/tinyproto
   * Put the downloaded library content to Arduino/libraries/tinyproto folder
   * Restart the Arduino IDE
   * You will find the examples in the Arduino IDE under File->Examples->tinyproto

 * Arduino Option 2 (only library without docs)
   * Go to Arduino Library manager
   * Find and install tinyproto library
   * Restart the Arduino IDE
   * You will find the examples in the Arduino IDE under File->Examples->tinyproto

 * ESP32 IDF
   * Download sources from https://github.com/lexus2k/tinyproto and put to components
     folder of your project
   * Run `make` for your project

 * Linux
   * Download sources from https://github.com/lexus2k/tinyproto
   * Run `make` command from tinyproto folder, and it will build library and tools for you

 * Plain AVR
   * Download sources from https://github.com/lexus2k/tinyproto
   * Install avr gcc compilers
   * Run `make ARCH=avr`

## Using tiny_loopback tool

 * Connect your Arduino board to PC
 * Run your sketch or tinylight_loopback
 * Compile tiny_loopback tool
 * Run tiny_loopback tool: `./bld/tiny_loopback -p /dev/ttyUSB0 -t light -g -c 8 -a -r`

 * Connect your Arduino board to PC
 * Run your sketch or tinyfd_loopback
 * Compile tiny_loopback tool
 * Run tiny_loopback tool: `./bld/tiny_loopback -p /dev/ttyUSB0 -t fd -c 8 -w 3 -g -a -r`

For more information about this library, please, visit https://github.com/lexus2k/tinyproto.
Doxygen documentation can be found at [Codedocs xyz site](https://codedocs.xyz/lexus2k/tinyproto).
If you found any problem or have any idea, please, report to Issues section.

## License

Copyright 2016-2021 (C) Alexey Dynda

This file is part of Tiny Protocol Library.

Protocol Library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Protocol Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Protocol Library.  If not, see <http://www.gnu.org/licenses/>.

