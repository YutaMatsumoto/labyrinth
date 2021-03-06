# Install script for directory: /home/yuta/icehockey/assimp/code

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3.0.1264"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/yuta/icehockey/assimp/lib/libassimp.so.3.0.1264"
    "/home/yuta/icehockey/assimp/lib/libassimp.so.3"
    "/home/yuta/icehockey/assimp/lib/libassimp.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3.0.1264"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp3.0-r1264")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/yuta/icehockey/assimp/code/../include/assimp/anim.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/ai_assert.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/camera.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/color4.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/color4.inl"
    "/home/yuta/icehockey/assimp/code/../include/assimp/config.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/defs.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/cfileio.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/light.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/material.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/material.inl"
    "/home/yuta/icehockey/assimp/code/../include/assimp/matrix3x3.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/matrix3x3.inl"
    "/home/yuta/icehockey/assimp/code/../include/assimp/matrix4x4.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/matrix4x4.inl"
    "/home/yuta/icehockey/assimp/code/../include/assimp/mesh.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/postprocess.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/quaternion.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/quaternion.inl"
    "/home/yuta/icehockey/assimp/code/../include/assimp/scene.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/texture.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/types.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/vector2.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/vector2.inl"
    "/home/yuta/icehockey/assimp/code/../include/assimp/vector3.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/vector3.inl"
    "/home/yuta/icehockey/assimp/code/../include/assimp/version.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/cimport.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/importerdesc.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/Importer.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/IOStream.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/IOSystem.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/Logger.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/LogStream.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/NullLogger.hpp"
    "/home/yuta/icehockey/assimp/code/../include/assimp/cexport.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/Exporter.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/yuta/icehockey/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/home/yuta/icehockey/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/home/yuta/icehockey/assimp/code/pstdint.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")

