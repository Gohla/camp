
# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 7)
set(VERSION_PATCH 1)
set(VERSION_STR "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("Project version: ${VERSION_STR}")

# Set the default build type to release with debug info
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo
        CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    )
endif()

# Add an option for choosing the build type (shared or static)
if(NOT BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS TRUE
        CACHE BOOL "TRUE to build CAMP as a shared library, FALSE to build it as a static library."
    )
endif()

# Add an option for if strings should be copied inside a camp::Value
if(NOT COPY_STRINGS)
    set(COPY_STRINGS FALSE
        CACHE BOOL "TRUE to copy strings inside a camp::Value, FALSE to reference strings inside a camp::Value."
    )
endif()

# Set the default test build option to false
if(NOT BUILD_TEST)
    set(BUILD_TEST FALSE
        CACHE BOOL "TRUE to build the unit tests (requires the Boost Test Library), FALSE otherwise."
    )
endif()

# Set the default test build option to false
if(NOT BUILD_TEST_QT)
    set(BUILD_TEST_QT FALSE
        CACHE BOOL "TRUE to build the Qt-specific unit tests (requires the Boost Test Library and Qt 4.5), FALSE otherwise."
    )
endif()

# Lua scripting module
if(NOT BUILD_LUA)
    set(BUILD_LUA FALSE
        CACHE BOOL "TRUE to enable building of the lua module, FALSE to disable."
    )
endif()

# Lua scripting module tets
if(NOT BUILD_TEST_LUA)
    set(BUILD_TEST_LUA FALSE
        CACHE BOOL "TRUE to enable building of the lua module tests, FALSE to disable."
    )
endif()

# define install directory for miscelleneous files
if(WIN32 AND NOT UNIX)
    set(INSTALL_MISC_DIR .)
elseif(UNIX)
    set(INSTALL_MISC_DIR share/camp)
endif()

# setup MacOSX build environment if necessary
include(${CMAKE_SOURCE_DIR}/cmake/MacOSX.cmake)

