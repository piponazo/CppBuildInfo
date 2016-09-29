# CppBuildInfo
[![Build Status](https://travis-ci.org/piponazo/CppBuildInfo.svg?branch=master)](https://travis-ci.org/piponazo/CppBuildInfo)

Application for measuring / analyzing build times in C++ projects.

This project includes two applications:

* A small command line application that must be called suffixing each compilation command (it measures the compilation time)
* A GUI application for representing the information gathered with the former app.

## Configuration of this project with CMake

This application only depends on Qt 4.8. Initially I tried QtCharts (included in 5.7) but at the end
I ended up using the Qt Graphics View Framework included since Qt 4.

In order to configure the project properly with CMake, you could need to set the QTDIR environment 
variable and add the qmake executable to your PATH. This will depend on the Operative System used. 
Normally on Linux you do not need to take care of that. Therefore, the configuration of the project
should be as easy as:

```text
CppBuildInfo$ mkdir build && cd build
CppBuildInfo/buildRelease$ cmake ../ 
```

## Integration with your C++ projects

### Using CMake

For prefixing cppTimeBuild before each compilation command, you just need to set the RULE_LAUNCH_COMPILE property:

```text
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "/usr/local/bin/cppTimeClient --outputFile /tmp/prueba.txt")
```
