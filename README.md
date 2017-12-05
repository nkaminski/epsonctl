# epsonctl 

A small utility for controlling Epson Powerlite projectors over thier RS232 port.

## Building

No dependencies are required beyond a working C compiler and the standard C libraries.

    make

To install to /usr/bin

    (as root) make install

## Usage

    epsonctl <serial_port> on|off|bright|dim|blank|unblank|computer1|computer2|composite|svideo
