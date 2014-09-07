Mictool
=======

This project is a CLI based tool compatible to JMic by TUM.

Functions:
- parse MPR files and output them as formatted HTML (planned: LaTeX)

Usage
-----

**mictool** \[**--help**\] \[**--version**\] _inputfile_ **-o** _outputfile_

where _inputfile_ should be an MPR file and _outputfile_ an HTML file.
_outputfile_ will be created if not found and will be overwritten otherwise.


Compatibility
-------------

Compiled and tested with Debian 7 (wheezy) amd64 and GNU C++ compiler 4.7.2 .
Should be working with MinGW (GCC, Make) on Windows as well.

For cross compiling on Linux for Windows install package mingw-w32 and use
the make files Makefile.win32 and Makefile.win64.
