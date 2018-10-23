# CppBuildInfo
[![Build Status](https://travis-ci.org/piponazo/CppBuildInfo.svg?branch=master)](https://travis-ci.org/piponazo/CppBuildInfo)

Application for measuring / analyzing build times in C++ projects.

This project includes two applications:

* A simple command line application that must be called suffixing each compilation command (it measures the compilation time) for measuring the compilation time.
* A GUI application for representing the information gathered with the former app.

## Configuration of this project with CMake

This application only depends on Qt 5.9 (and GTest for compiling and running the tests).

In order to configure the project properly with CMake, you could need to set the QTDIR environment
variable and add the directory where the qmake executable is your PATH environment variable. This
will depend on the Operative System used.

Normally on Linux you do not need to take care of that. Therefore, the configuration of the project
should be as easy as:

```text
CppBuildInfo$ mkdir build && cd build
CppBuildInfo/buildRelease$ cmake -DCMAKE_PREFIX_PATH=/path/to/Qt/installation ../ 
```

## Integration with your C++ projects

### Using CMake

For prefixing cppTimeBuild before each compilation command, you just need to set the RULE_LAUNCH_COMPILE property:

```text
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "/usr/local/bin/cppTimeClient --outputFile /tmp/output.txt")
```
