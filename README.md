Mictool
=======

This project is a CLI based tool compatible to JMic by TUM.

Functions:
- parse MPR files and output them as formatted HTML (*.html) or LaTeX (*.tex)

Usage
-----

**mictool** \[**--help**\] \[**--version**\] _inputfile_ **-o** _outputfile_

where _inputfile_ should be an MPR file and _outputfile_ an HTML or tex file.
_outputfile_ will be created if not found and will be overwritten otherwise.

Code Formatting
---------------

- use tabs for intendation
- brackets on the same line

Compatibility
-------------

Compiled and tested with Debian 7 (wheezy) amd64 and GNU C++ compiler 4.7.2.
Also tested on Ubuntu 14.04 with g++ 4.8.2 and Cygwin on Win7.
Should be working with MinGW (GCC, Make) on Windows and RaspberryPi with Raspbian as well.

For cross compiling on Linux for Windows install package mingw-w32 and use
the make files Makefile.win32 and Makefile.win64.
