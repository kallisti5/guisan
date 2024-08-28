CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
#SET(CMAKE_MODULE_PATH "cmake_modules/")

PROJECT(guisan)

SET(MAJOR_VERSION 1)
SET(MINOR_VERSION 1)
SET(PATCH_LEVEL 0)
SET(${PROJECT_NAME}_SOVERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_LEVEL})
SET(${PROJECT_NAME}_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_LEVEL})

# set default cmake build type to RelWithDebInfo (None Debug Release RelWithDebInfo MinSizeRel)
#IF( NOT CMAKE_BUILD_TYPE )
#  SET( CMAKE_BUILD_TYPE "RelWithDebInfo" )
#ENDIF()

# set default install prefix to project root directory
#IF (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local" )
#  SET( CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}" )
#ENDIF()

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
ADD_COMPILE_DEFINITIONS(GUICHAN_BUILD GUICHAN_EXTENSION_BUILD)

# The Guisan core library
FILE(GLOB GUISAN_HEADER include/guisan.hpp)
FILE(GLOB GUISAN_HEADERS
  include/guisan/actionevent.hpp
  include/guisan/actionlistener.hpp
  include/guisan/basiccontainer.hpp
  include/guisan/cliprectangle.hpp
  include/guisan/color.hpp
  include/guisan/deathlistener.hpp
  include/guisan/defaultfont.hpp
  include/guisan/event.hpp
  include/guisan/exception.hpp
  include/guisan/focushandler.hpp
  include/guisan/focuslistener.hpp
  include/guisan/font.hpp
  include/guisan/genericinput.hpp
  include/guisan/graphics.hpp
  include/guisan/gui.hpp
  include/guisan/image.hpp
  include/guisan/imagefont.hpp
  include/guisan/imageloader.hpp
  include/guisan/input.hpp
  include/guisan/inputevent.hpp
  include/guisan/key.hpp
  include/guisan/keyevent.hpp
  include/guisan/keyinput.hpp
  include/guisan/keylistener.hpp
  include/guisan/listmodel.hpp
  include/guisan/mouseevent.hpp
  include/guisan/mouseinput.hpp
  include/guisan/mouselistener.hpp
  include/guisan/platform.hpp
  include/guisan/rectangle.hpp
  include/guisan/selectionevent.hpp
  include/guisan/selectionlistener.hpp
  include/guisan/widget.hpp
  include/guisan/widgetlistener.hpp
)
FILE(GLOB GUISAN_WIDGET_HEADERS include/guisan/widgets/*.hpp)
FILE(GLOB GUISAN_CONTRIB_WIDGET_HEADERS include/guisan/contrib/widgets/*.hpp)
FILE(GLOB GUISAN_SRC src/*.cpp src/widgets/*.cpp)

OPTION(BUILD_GUISAN_SHARED "Build the Guisan core library as a shared library." ON)
IF(BUILD_GUISAN_SHARED)
  SET(GUISAN_LIBRARY_TYPE SHARED)
ELSE(BUILD_GUISAN_SHARED)
  SET(GUISAN_LIBRARY_TYPE STATIC)
ENDIF(BUILD_GUISAN_SHARED)

ADD_LIBRARY(${PROJECT_NAME} ${GUISAN_LIBRARY_TYPE} ${GUISAN_SRC} )
ADD_CUSTOM_TARGET(lib DEPENDS ${PROJECT_NAME}) # Create symlink

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
   VERSION ${${PROJECT_NAME}_VERSION}
   SOVERSION ${${PROJECT_NAME}_SOVERSION}
   CLEAN_DIRECT_OUTPUT 1 # Allow creating static and shared libraries without conflict
   OUTPUT_NAME ${PROJECT_NAME}) # Avoid conflicts between library and binary target names

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION lib PERMISSIONS
  OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE)
INSTALL(FILES ${GUISAN_HEADER} DESTINATION include/)
INSTALL(FILES ${GUISAN_HEADERS} DESTINATION include/guisan/)
INSTALL(FILES ${GUISAN_WIDGET_HEADERS} DESTINATION include/guisan/widgets/)
INSTALL(FILES ${GUISAN_CONTRIB_WIDGET_HEADERS} DESTINATION include/guisan/contrib/widgets/)

# The Guisan OpenGL extension library
OPTION(ENABLE_OPENGL "Enable the Guisan OpenGL extension" ON)
OPTION(BUILD_GUISAN_OPENGL_SHARED "Build the Guisan OpenGL extension library as a shared library." ON)
FIND_PACKAGE(OpenGL)
IF(ENABLE_OPENGL AND OPENGL_FOUND)
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
  FILE(GLOB GUISAN_OPENGL_HEADER include/guisan/opengl.hpp)
  FILE(GLOB GUISAN_OPENGL_HEADERS include/guisan/opengl/*.hpp)
  FILE(GLOB GUISAN_OPENGL_CONTRIB_HEADERS include/guisan/opengl/contrib/*.hpp)
  FILE(GLOB GUISAN_OPENGL_SRC src/opengl/*.cpp)
  IF(BUILD_GUISAN_OPENGL_SHARED)
    SET(GUISAN_OPENGL_LIBRARY_TYPE SHARED)
  ELSE(BUILD_GUISAN_OPENGL_SHARED)
    SET(GUISAN_OPENGL_LIBRARY_TYPE STATIC)
  ENDIF(BUILD_GUISAN_OPENGL_SHARED)
  ADD_LIBRARY(${PROJECT_NAME}_opengl ${GUISAN_OPENGL_LIBRARY_TYPE} ${GUISAN_OPENGL_SRC} )
  IF(WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}_opengl ${OPENGL_LIBRARY} ${PROJECT_NAME})
  ENDIF(WIN32)
  ADD_CUSTOM_TARGET(lib DEPENDS ${PROJECT_NAME}_opengl) # Create symlink
  SET_TARGET_PROPERTIES(${PROJECT_NAME}_opengl PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    CLEAN_DIRECT_OUTPUT 1 # Allow creating static and shared libraries without conflict
    OUTPUT_NAME ${PROJECT_NAME}_opengl) # Avoid conflicts between library and binary target names
  INSTALL(TARGETS ${PROJECT_NAME}_opengl DESTINATION lib PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)
  INSTALL(FILES ${GUISAN_OPENGL_HEADER} DESTINATION include/guisan/)
  INSTALL(FILES ${GUISAN_OPENGL_HEADERS} DESTINATION include/guisan/opengl/)
  INSTALL(FILES ${GUISAN_OPENGL_CONTRIB_HEADERS} DESTINATION include/guisan/contrib/opengl/)
ENDIF(ENABLE_OPENGL AND OPENGL_FOUND)

# The Guisan SDL extension library
OPTION(ENABLE_SDL "Enable the Guisan SDL extension" ON)
OPTION(BUILD_GUISAN_SDL_SHARED "Build the Guisan SDL extension library as a shared library." ON)
FIND_PACKAGE(SDL)
FIND_PACKAGE(SDL_image)
IF(ENABLE_SDL AND SDL_FOUND AND SDLIMAGE_FOUND)
  INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
  FILE(GLOB GUISAN_SDL_HEADER include/guisan/sdl.hpp)
  FILE(GLOB GUISAN_SDL_HEADERS include/guisan/sdl/*.hpp)
  FILE(GLOB GUISAN_SDL_CONTRIB_HEADERS include/guisan/contrib/sdl/*.hpp)
  FILE(GLOB GUISAN_SDL_SRC src/sdl/*.cpp)
  IF(BUILD_GUISAN_SDL_SHARED)
    SET(GUISAN_SDL_LIBRARY_TYPE SHARED)
  ELSE(BUILD_GUISAN_SDL_SHARED)
    SET(GUISAN_SDL_LIBRARY_TYPE STATIC)
  ENDIF(BUILD_GUISAN_SDL_SHARED)
  ADD_LIBRARY(${PROJECT_NAME}_sdl ${GUISAN_SDL_LIBRARY_TYPE} ${GUISAN_SDL_SRC} )
  IF(WIN32)
    IF(MINGW)
      TARGET_LINK_LIBRARIES(${PROJECT_NAME}_sdl ${MINGW32_LIBRARY} ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} SDLmain ${PROJECT_NAME})
    ELSE(MINGW)
      TARGET_LINK_LIBRARIES(${PROJECT_NAME}_sdl ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} SDLmain)
    ENDIF(MINGW)
  ENDIF(WIN32)
  ADD_CUSTOM_TARGET(lib DEPENDS ${PROJECT_NAME}_sdl) # Create symlink
  SET_TARGET_PROPERTIES(${PROJECT_NAME}_sdl PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_SOVERSION}
    CLEAN_DIRECT_OUTPUT 1 # Allow creating static and shared libraries without conflict
    OUTPUT_NAME ${PROJECT_NAME}_sdl) # Avoid conflicts between library and binary target names
  INSTALL(TARGETS ${PROJECT_NAME}_sdl DESTINATION lib PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)
  INSTALL(FILES ${GUISAN_SDL_HEADER} DESTINATION include/guisan/)
  INSTALL(FILES ${GUISAN_SDL_HEADERS} DESTINATION include/guisan/sdl/)
  INSTALL(FILES ${GUISAN_SDL_CONTRIB_HEADERS} DESTINATION include/guisan/contrib/sdl/)
ENDIF(ENABLE_SDL AND SDL_FOUND AND SDLIMAGE_FOUND)

# Make uninstall target
#CONFIGURE_FILE(
#  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
#  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
#  IMMEDIATE @ONLY)
#ADD_CUSTOM_TARGET(uninstall
#  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

MESSAGE(STATUS "Guisan has been built, hooray!")
# MESSAGE( STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}" )
# MESSAGE( STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}" )
# MESSAGE( STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )
# MESSAGE( STATUS "${PROJECT_NAME}_DEPENDS = \"${${PROJECT_NAME}_DEPENDS}\"" )
# MESSAGE( STATUS "BUILD_WITH = \"${BUILD_WITH}\"" )
# MESSAGE( STATUS "INSTALL_DOC = ${INSTALL_DOC}" )
# MESSAGE( STATUS "Change a value with: cmake -D<Variable>=<Value>" )
# MESSAGE( STATUS "-------------------------------------------------------------------------------" )
# MESSAGE( STATUS )

# # force some variables that could be defined in the command line to be written to cache
#SET(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS}" CACHE BOOL "Set to OFF to build static libraries" FORCE)
# SET( CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE PATH
#   "Where to install ${PROJECT_NAME}" FORCE )
# SET( CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
#   "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
# SET( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" CACHE PATH
#   "Path to custom CMake Modules" FORCE )
# SET( INSTALL_DOC "${INSTALL_DOC}" CACHE BOOL
#   "Set to OFF to skip build/install Documentation" FORCE )
# # export build settings
# INCLUDE( CMakeExportBuildSettings )
# CMAKE_EXPORT_BUILD_SETTINGS( "${PROJECT_NAME}BuildSettings.cmake" )
# # export library dependencies (keep this as the last line in the file)
# EXPORT_LIBRARY_DEPENDENCIES( "${PROJECT_NAME}LibDeps.cmake" )
