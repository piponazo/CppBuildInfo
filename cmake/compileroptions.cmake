set(EXTRA_C_FLAGS "")
set(EXTRA_C_FLAGS_RELEASE "")
set(EXTRA_C_FLAGS_DEBUG "")
set(EXTRA_EXE_LINKER_FLAGS "")
set(EXTRA_EXE_LINKER_FLAGS_RELEASE "")
set(EXTRA_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED 14)

# Common compiler flags for clang and gcc
# TODO : Include support for Clang
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)

   if(WARNINGS_ANSI_ISO)
      set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -pedantic -Wextra")
   endif()

   if(WARNINGS_ARE_ERRORS)
      set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Werror")
   endif()

   if(WARNINGS_EFFCPP)
      set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Weffc++")
   endif()

   set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wall -Werror=return-type")

endif()

IF (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)

    set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -fvisibility=hidden") # All the symbols will be hidden by default.
    set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wreturn-type")
    set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wno-long-long")
    set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wno-maybe-uninitialized")

    if(WARNINGS_ANSI_ISO)
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wstrict-aliasing=3")
    else()
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wno-narrowing")
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wno-delete-non-virtual-dtor")
        set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS} -Wno-unnamed-type-template-args")
    endif()

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    message(FATAL_ERROR "Clang not supported yet")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    #    message(FATAL_ERROR "MSVC not supported yet")

endif()

# Add user supplied extra options (optimization, etc...)
# ==========================================================
set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS}" CACHE INTERNAL "Extra compiler options")
set(EXTRA_C_FLAGS_RELEASE "${EXTRA_C_FLAGS_RELEASE}" CACHE INTERNAL "Extra compiler options for Release build")
set(EXTRA_C_FLAGS_DEBUG "${EXTRA_C_FLAGS_DEBUG}" CACHE INTERNAL "Extra compiler options for Debug build")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  ${EXTRA_C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${EXTRA_C_FLAGS_DEBUG}")

set(CMAKE_EXE_LINKER_FLAGS         "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${EXTRA_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG   "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${EXTRA_EXE_LINKER_FLAGS_DEBUG}")
