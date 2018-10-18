# Common compiler flags for clang and gcc
# TODO : Include support for Clang
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)

   if(WARNINGS_ANSI_ISO)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wextra")
   endif()

   if(WARNINGS_ARE_ERRORS)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
   endif()

   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wreturn-type")

endif()

if (MSVC)
    if ( EXIV2_EXTRA_WARNINGS )
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif ()

    # Object Level Parallelism
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
