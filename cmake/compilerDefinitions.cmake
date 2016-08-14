##########################################
# Qt library definitions
##########################################
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        add_definitions(-DQT_NO_DEBUG)
        add_definitions(-DQT_NO_DEBUG_OUTPUT)
        add_definitions(-DQT_NO_WARNING_OUTPUT)
else()
        add_definitions(-DQT_DEBUG)
endif()
