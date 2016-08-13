# CppBuildInfo
Application for measuring / analyzing build times in C++ projects.

This project includes two applications:

* A small command line application that must be called suffixing each compilation command (it measures the compilation time)
* A GUI application for representing the information gathered with the former app.

## Configuration of this project with CMake

This application only depends on Qt 5.7. These are some of the reasons of this choose:

* QtCore for simplifying the execution of the compilation command (with QProcess). It should be platform-independent.
* QtWidgets and QtCharts for the graphical application.

In order to configure the project properly with cmake, you will need to specify the path of your Qt5 installation directory with *CMAKE_PREFIX_PATH*:

```text
CppBuildInfo$ mkdir buildRelease && cd buildRelease
CppBuildInfo/buildRelease$ cmake ../ -DCMAKE_PREFIX_PATH=/opt/Qt5.7.0/5.7/gcc_64/
```


## Integration with your C++ projects

### Using CMake

For prefixing cppTimeBuild before each compilation command, you just need to set the RULE_LAUNCH_COMPILE property:

```text
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "/usr/local/bin/cppTimeClient --outputFile /tmp/prueba.txt")
```
