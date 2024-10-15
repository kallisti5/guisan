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

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
ADD_COMPILE_DEFINITIONS(GUICHAN_BUILD GUICHAN_EXTENSION_BUILD)

# The Guisan core library
SET(GUISAN_HEADER include/guisan.hpp)
SET(GUISAN_HEADERS
  include/guisan/actionevent.hpp
  include/guisan/actionlistener.hpp
  include/guisan/cliprectangle.hpp
  include/guisan/color.hpp
  include/guisan/containerevent.hpp
  include/guisan/containerlistener.hpp
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
  include/guisan/text.hpp
  include/guisan/widget.hpp
  include/guisan/widgetlistener.hpp
)
FILE(GLOB GUISAN_WIDGET_HEADERS include/guisan/widgets/*.hpp)
FILE(GLOB GUISAN_CONTRIB_WIDGET_HEADERS include/guisan/contrib/widgets/*.hpp)
FILE(GLOB GUISAN_SRC src/*.cpp)
FILE(GLOB GUISAN_WIDGET_SRC src/widgets/*.cpp)

# Grouping of the source for nicer display in IDEs such as Visual Studio
SOURCE_GROUP(src FILES ${GUISAN_HEADER})
SOURCE_GROUP(src/guisan FILES ${GUISAN_HEADERS} ${GUISAN_SRC})
SOURCE_GROUP(src/guisan/widgets FILES ${GUISAN_WIDGET_HEADERS} ${GUISAN_WIDGET_SRC})
SOURCE_GROUP(src/guisan/contrib/widgets FILES ${GUISAN_CONTRIB_WIDGET_HEADERS})

OPTION(BUILD_GUISAN_SHARED "Build the Guisan core library as a shared library." ON)
IF(BUILD_GUISAN_SHARED)
  SET(GUISAN_LIBRARY_TYPE SHARED)
ELSE(BUILD_GUISAN_SHARED)
  SET(GUISAN_LIBRARY_TYPE STATIC)
ENDIF(BUILD_GUISAN_SHARED)

ADD_LIBRARY(${PROJECT_NAME} ${GUISAN_LIBRARY_TYPE}
	${GUISAN_HEADER}
	${GUISAN_HEADERS}
	${GUISAN_WIDGET_HEADERS}
	${GUISAN_CONTRIB_WIDGET_HEADERS}
	${GUISAN_SRC}
	${GUISAN_WIDGET_SRC})

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

  # The Guisan OpenGL extension source
  FILE(GLOB GUISAN_OPENGL_HEADER include/guisan/opengl.hpp)
  FILE(GLOB GUISAN_OPENGL_HEADERS include/guisan/opengl/*.hpp)
  FILE(GLOB GUISAN_OPENGL_CONTRIB_HEADERS include/guisan/opengl/contrib/*.hpp)
  FILE(GLOB GUISAN_OPENGL_SRC src/opengl/*.cpp)

  # Grouping of the source for nicer display in IDEs such as Visual Studio
  SOURCE_GROUP(src/guisan FILES ${GUISAN_OPENGL_HEADER})
  SOURCE_GROUP(src/guisan/opengl FILES ${GUISAN_OPENGL_HEADERS} ${GUISAN_OPENGL_SRC})
  SOURCE_GROUP(src/guisan/contrib/opengl FILES ${GUISAN_OPENGL_CONTRIB_HEADERS})

  IF(BUILD_GUISAN_OPENGL_SHARED)
    SET(GUISAN_OPENGL_LIBRARY_TYPE SHARED)
  ELSE(BUILD_GUISAN_OPENGL_SHARED)
    SET(GUISAN_OPENGL_LIBRARY_TYPE STATIC)
  ENDIF(BUILD_GUISAN_OPENGL_SHARED)
  ADD_LIBRARY(${PROJECT_NAME}_opengl ${GUISAN_OPENGL_LIBRARY_TYPE}
	${GUISAN_OPENGL_HEADER}
	${GUISAN_OPENGL_HEADERS}
	${GUISAN_OPENGL_CONTRIB_HEADERS}
	${GUISAN_OPENGL_SRC})
  IF(WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}_opengl ${OPENGL_LIBRARY} ${PROJECT_NAME})
  ENDIF(WIN32)

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
OPTION(ENABLE_SDL_TTF "Enable the Guisan SDL TTF extension" ON)
OPTION(BUILD_GUISAN_SDL_SHARED "Build the Guisan SDL extension library as a shared library." ON)

IF(ENABLE_SDL)
  FIND_PACKAGE(SDL2 REQUIRED)
  FIND_PACKAGE(SDL2_image REQUIRED)

  INCLUDE_DIRECTORIES(SYSTEM ${SDL2_INCLUDE_DIR})

  # The Guichan SDL extension source
  FILE(GLOB GUISAN_SDL_HEADER include/guisan/sdl.hpp)
  FILE(GLOB GUISAN_SDL_HEADERS include/guisan/sdl/*.hpp)
  FILE(GLOB GUISAN_SDL_CONTRIB_HEADERS include/guisan/contrib/sdl/*.hpp)
  FILE(GLOB GUISAN_SDL_SRC src/sdl/*.cpp)

  # Grouping of the source for nicer display in IDEs such as Visual Studio
  SOURCE_GROUP(src/guisan FILES ${GUISAN_SDL_HEADER})
  SOURCE_GROUP(src/guisan/sdl FILES ${GUISAN_SDL_HEADERS} ${GUISAN_SDL_SRC})
  SOURCE_GROUP(src/guisan/contrib/sdl FILES ${GUISAN_SDL_CONTRIB_HEADERS})

  IF(BUILD_GUISAN_SDL_SHARED)
    SET(GUISAN_SDL_LIBRARY_TYPE SHARED)
  ELSE(BUILD_GUISAN_SDL_SHARED)
    SET(GUISAN_SDL_LIBRARY_TYPE STATIC)
  ENDIF(BUILD_GUISAN_SDL_SHARED)
  ADD_LIBRARY(${PROJECT_NAME}_sdl ${GUISAN_SDL_LIBRARY_TYPE}
	${GUISAN_SDL_HEADER}
	${GUISAN_SDL_HEADERS}
	${GUISAN_SDL_CONTRIB_HEADERS}
	${GUISAN_SDL_SRC})
  if(TARGET SDL2::SDL2main)
    MESSAGE(STATUS "SDL2main used")
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME}_sdl PRIVATE SDL2::SDL2main)
  endif()
  IF(MINGW)
    MESSAGE(STATUS "MINGW32_LIBRARY: ${MINGW32_LIBRARY}")
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}_sdl ${MINGW32_LIBRARY})
  ENDIF(MINGW)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME}_sdl PRIVATE SDL2::SDL2 SDL2_image::SDL2_image ${PROJECT_NAME})
  IF(ENABLE_SDL_TTF)
    FIND_PACKAGE(SDL2_ttf REQUIRED)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}_sdl PRIVATE SDL2_ttf::SDL2_ttf)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME}_sdl PUBLIC USE_SDL2_TTF)
  ENDIF(ENABLE_SDL_TTF)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME}_sdl PRIVATE ${PROJECT_NAME})

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
ENDIF(ENABLE_SDL)

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
