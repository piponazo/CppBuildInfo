# CppBuildInfo
Application for measuring / analyzing build times in C++ projects

## Integration with your C++ projects

### Using CMake

For prefixing cppTimeBuild before each compilation command, you just need to set the RULE_LAUNCH_COMPILE property:

```text
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "/usr/local/bin/cppTimeClient --outputFile /tmp/prueba.txt")
```
