# Install script for directory: /Users/karthic/15462/asst5_waterbunny/CMU462/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/karthic/15462/asst5_waterbunny/build/CMU462/src/libCMU462.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCMU462.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCMU462.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCMU462.a")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CMU462" TYPE FILE FILES
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/CMU462.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/vector2D.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/vector3D.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/vector4D.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/matrix3x3.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/matrix4x4.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/quaternion.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/complex.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/color.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/osdtext.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/viewer.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/base64.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/tinyxml2.h"
    "/Users/karthic/15462/asst5_waterbunny/CMU462/src/renderer.h"
    )
endif()

