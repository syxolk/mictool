Mictool
=======

This project is a CLI based tool compatible to JMic by TUM.

Functions:
- parse MPR files and output them as formatted HTML (*.html) or LaTeX (*.tex)

Installation
------------

You need git, make and g++ installed.

```
git clone https://github.com/syxolk/mictool.git
cd mictool
make
sudo make install
```

Usage
-----

**mictool** \[**--help**\] \[**--version**\] _inputfile_ **-o** _outputfile_

where _inputfile_ should be an MPR file and _outputfile_ an HTML or tex file.
_outputfile_ will be created if not found and will be overwritten otherwise.
The output format will be auto detected by filename extension.

**mictool** **-o** _outputfile_

where the input must be provided from standard input, for example with **cat**.

**mictool** _inputfile_ \[**--html**\] \[**--latex**\] \[**--debug**\]

where the output will come out to the standard output and can be
redirected to a file or another program. One of the output formatting
parameters must be given.

**mictool** \[**--html**\] \[**--latex**\] \[**--debug**\]

where the input and the output must be provided from standard input and output.

For more information try

**mictool** **--help**

or after installation

**man** **mictool**

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
