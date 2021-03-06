Mictool
=======

Mictool parses MPR files and outputs them in human-readable formats
like HTML or LaTeX. It's a command line based tool, compatible to the
save files of JMic by TUM.

Functions:
- parse MPR files and output them as formatted HTML (*.html) or LaTeX (*.tex)

Further information:
- Input/output can be piped from/to the standard input/output. (See Usage)
- Can be compiled on Windows with Cygwin/MinGW (See Compatibility).
- Only standard c++0x is used (except for getopt.h).

Installation
------------

You need git, make and g++ installed.

    git clone https://github.com/syxolk/mictool.git
    cd mictool
    mkdir release
    cd release
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DGTEST_ROOT=/usr/src/gtest/build ..
    make
    
For compiling the test suite and running the tests you need GTest.
Example for linux users:

    apt-get install libgtest-dev # or download source to /usr/src/gtest
    cd /usr/src/gtest
    mkdir build
    cd build
    cmake ..
    make

Usage
-----

    mictool [--help] [--version] INPUTFILE -o OUTPUTFILE.

where _inputfile_ should be an MPR file and _outputfile_ an HTML or tex file.
_outputfile_ will be created if not found and will be overwritten otherwise.
The output format will be auto detected by filename extension.

    mictool -o OUTPUTFILE

where the input must be provided from standard input, for example with **cat**.

    mictool INPUTFILE [--html] [--latex] [--debug]

where the output will come out to the standard output and can be
redirected to a file or another program. One of the output formatting
parameters must be given.

    mictool [--html] [--latex] [--debug] [--title TITLE]

where the input and the output must be provided from standard input and output.
The title option sets the title for HTML and LaTeX documents explicitly.

For more information try

    mictool --help

or after installation

    man mictool

Code Formatting
---------------

- use tabs for intendation
- brackets on the same line

Documentation
-------------

Generate a source code documentation with

    make doc

Tests
-----

Start tests with

    make test

or execute directly the test executable

    ./mictool_test

Compatibility
-------------

Compiled and tested with Debian 7 (wheezy) amd64 and GNU C++ compiler 4.7.2.
Also tested on Ubuntu 14.04 with g++ 4.8.2 and Cygwin on Win7.
Should be working with MinGW (GCC, Make) on Windows and RaspberryPi with Raspbian as well.

**VISUAL STUDIO:** Currently no support. Try cygwin or mingw in the mean time.
