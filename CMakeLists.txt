cmake_minimum_required(VERSION 3.16)

# Safer policy handling. You do not need this CMP0048 check anymore at 3.16,
# but keeping it harmless.
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

# Build emscripten version
option(BUILD_EMSCRIPTEN "Build with Emscripten toolchain" OFF)

# If you want emscripten, use a toolchain file in practice.
# This keeps your old behavior without exploding immediately.
if(BUILD_EMSCRIPTEN)
  set(CMAKE_C_COMPILER /usr/local/bin/emcc CACHE FILEPATH "" FORCE)
  set(CMAKE_CXX_COMPILER /usr/local/bin/em++ CACHE FILEPATH "" FORCE)
endif()

project(KEngine VERSION 0.4
  DESCRIPTION "OpenGL 2D game engine"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json for IntelliSense and tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(UNIX AND NOT APPLE)
  set(OpenGL_GL_PREFERENCE "GLVND")
  set(LINUX TRUE)
endif()

if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

# Library name
set(KENGINE_LIBRARY_NAME "kengine")

# Debug mode
option(KENGINE_DEBUG_MODE "Build in debug mode" ON)

# Build editor
option(KENGINE_BUILD_EDITOR "Build engine editor" ON)

# Build examples (optional)
option(BUILD_KENGINE_EXAMPLES "Build examples if present" ON)

# Build tests
option(BUILD_KENGINE_TESTS "Build tests" OFF)

# Turn these on to use system libraries (Linux and macOS)
option(USE_SYSTEM_SDL2 "Search your system for SDL2 library" ON)
option(USE_SYSTEM_OPENAL "Search your system for OpenAL and ALut libraries" ON)
option(USE_SYSTEM_VORBIS "Search your system for ogg and vorbis libraries" ON)
option(USE_SYSTEM_ENTT "Search your system for entt library" OFF)
option(USE_SYSTEM_FREETYPE "Search your system for FreeType2 library" ON)
option(USE_SYSTEM_LUA "Search your system for lua" ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Prefer target-based includes, but keep a single global include for your own headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(SYSTEM)

find_package(OpenGL REQUIRED)

# SDL2
if(USE_SYSTEM_SDL2 AND NOT WIN32)
  if(APPLE)
    find_package(SDL2 REQUIRED)
  else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(SDL2 REQUIRED sdl2)
  endif()
elseif(WIN32)
  set(SDL2_INCLUDE_DIRS ${DEPENDENCIES_DIR}/sdl2/include)
  set(SDL2_LIBRARIES ${DEPENDENCIES_DIR}/win/sdl2-x64/lib/x64/SDL2.lib)
else()
  set(SDL2_INCLUDE_DIRS ${DEPENDENCIES_DIR}/sdl2/include ${DEPENDENCIES_DIR}/sdl2/include/SDL2)
  set(SDL2_LIBRARIES SDL2)
endif()
include_directories(${SDL2_INCLUDE_DIRS})

# Dear ImGui
if(KENGINE_BUILD_EDITOR)
  add_compile_definitions(KENGINE_BUILD_EDITOR)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/editor/imgui)
endif()

# GLAD
if(NOT BUILD_EMSCRIPTEN)
  set(GLAD_INCLUDE_DIRS ${DEPENDENCIES_DIR}/glad/include)
  set(GLAD_LIBRARIES glad)
  include_directories(${GLAD_INCLUDE_DIRS})
endif()

# GLM
include_directories(${DEPENDENCIES_DIR}/glm)

# stb_image
include_directories(${DEPENDENCIES_DIR}/stb_image)

# OpenAL / ALUT
if(USE_SYSTEM_OPENAL AND NOT WIN32)
  find_package(OpenAL REQUIRED)
  find_package(ALUT REQUIRED)
elseif(WIN32)
  if(MINGW)
    add_definitions(-D_TIMESPEC_DEFINED)
    set(OpenAL_INCLUDE_DIRS ${DEPENDENCIES_DIR}/openal-soft/include/AL)
    set(OpenAL_LIBRARIES OpenAL32)
  elseif(MSVC)
    set(OpenAL_INCLUDE_DIRS ${DEPENDENCIES_DIR}/openal-soft/include/AL)
    set(OpenAL_LIBRARIES ${DEPENDENCIES_DIR}/win/openal-soft-x64/OpenAL32.lib)

    set(ALUT_INCLUDE_DIRS ${DEPENDENCIES_DIR}/freealut/include)
    set(ALUT_LIBRARIES
      ${DEPENDENCIES_DIR}/win/freealut-x64/alut.lib
      ${DEPENDENCIES_DIR}/win/freealut-x64/alut_static.lib
    )
  endif()
else()
  if(APPLE)
    find_library(OPENAL_LIBRARY OpenAL)
    set(OpenAL_LIBRARIES ${OPENAL_LIBRARY})
  else()
    set(OpenAL_INCLUDE_DIRS ${DEPENDENCIES_DIR}/openal-soft/include)
    set(OpenAL_LIBRARIES openal)
  endif()

  set(ALUT_INCLUDE_DIRS ${DEPENDENCIES_DIR}/freealut/include)
  set(ALUT_LIBRARIES alut)
endif()
include_directories(${OpenAL_INCLUDE_DIRS})
include_directories(${ALUT_INCLUDE_DIRS})

# Ogg / Vorbis
if(USE_SYSTEM_VORBIS AND NOT WIN32)
  find_package(OGG REQUIRED)
  find_package(VORBIS REQUIRED)
elseif(WIN32)
  set(OGG_INCLUDE_DIRS ${DEPENDENCIES_DIR}/ogg/include)
  set(OGG_LIBRARIES ${DEPENDENCIES_DIR}/win/ogg-x64/libogg.lib)

  set(VORBIS_INCLUDE_DIR ${DEPENDENCIES_DIR}/vorbis/include)
  set(VORBIS_LIBRARIES
    ${DEPENDENCIES_DIR}/win/vorbis-x64/vorbis.lib
    ${DEPENDENCIES_DIR}/win/vorbis-x64/vorbisfile.lib
    ${DEPENDENCIES_DIR}/win/vorbis-x64/vorbisenc.lib
  )
endif()
include_directories(${OGG_INCLUDE_DIRS})
include_directories(${VORBIS_INCLUDE_DIR})

# EnTT
if(USE_SYSTEM_ENTT)
  find_package(entt)
else()
  set(ENTT_INCLUDE_DIR ${DEPENDENCIES_DIR}/entt/src)
endif()
include_directories(${ENTT_INCLUDE_DIR})

# FreeType
if(USE_SYSTEM_FREETYPE AND NOT WIN32)
  find_package(Freetype)
else()
  set(FREETYPE_INCLUDE_DIRS ${DEPENDENCIES_DIR}/win/freetype-x64/include)
  set(FREETYPE_LIBRARIES ${DEPENDENCIES_DIR}/win/freetype-x64/win64/freetype.lib)
endif()
include_directories(${FREETYPE_INCLUDE_DIRS})

# Lua
if(USE_SYSTEM_LUA AND NOT WIN32)
  find_package(Lua REQUIRED)
else()
  if(APPLE)
    set(LUA_LIBRARIES ${DEPENDENCIES_DIR}/lua/macos/liblua53.a)
    set(LUA_INCLUDE_DIR ${DEPENDENCIES_DIR}/lua/macos)
  elseif(LINUX)
    set(LUA_LIBRARIES ${DEPENDENCIES_DIR}/lua/linux/liblua.a)
    set(LUA_INCLUDE_DIR ${DEPENDENCIES_DIR}/lua/linux)
  elseif(WIN32)
    set(LUA_LIBRARIES ${DEPENDENCIES_DIR}/lua/win64/lua53.lib)
    set(LUA_INCLUDE_DIR ${DEPENDENCIES_DIR}/lua/win64/include)
  endif()
endif()
include_directories(${LUA_INCLUDE_DIR})

# Sol2
set(SOL_INCLUDE_DIR ${DEPENDENCIES_DIR}/sol2/include)
include_directories(${SOL_INCLUDE_DIR})

# Cereal
set(CEREAL_INCLUDE_DIR ${DEPENDENCIES_DIR}/cereal/include)
include_directories(${CEREAL_INCLUDE_DIR})

# Dirent
if(MSVC)
  set(DIRENT_INCLUDE_DIR ${DEPENDENCIES_DIR}/dirent/include)
  include_directories(${DIRENT_INCLUDE_DIR})
endif()

# Platform specific libraries
set(PLATFORM_LIBRARIES)

if(LINUX)
  if(NOT USE_SYSTEM_SDL2)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    list(APPEND PLATFORM_LIBRARIES ${X11_X11_LIB} ${X11_LIBRARIES})

    if(X11_Xi_FOUND)
      list(APPEND PLATFORM_LIBRARIES ${X11_Xi_LIB})
    endif()
    if(X11_Xrandr_FOUND)
      list(APPEND PLATFORM_LIBRARIES ${X11_Xrandr_LIB})
    endif()
    if(X11_xf86vmode_FOUND)
      list(APPEND PLATFORM_LIBRARIES ${X11_Xxf86vm_LIB})
      include_directories(${X11_xf86vmode_INCLUDE_PATH})
    endif()
    if(X11_Xinerama_FOUND)
      list(APPEND PLATFORM_LIBRARIES ${X11_Xinerama_LIB})
    endif()
    if(X11_Xcursor_FOUND)
      list(APPEND PLATFORM_LIBRARIES ${X11_Xcursor_LIB})
    endif()
  endif()

  find_package(LibRt REQUIRED)
  include_directories(${LIBRT_INCLUDE_DIRS})
  list(APPEND PLATFORM_LIBRARIES ${LIBRT_LIBRARIES})

  find_package(LibM REQUIRED)
  include_directories(${LIBM_INCLUDE_DIRS})
  list(APPEND PLATFORM_LIBRARIES ${LIBM_LIBRARIES})

  find_package(LibDL REQUIRED)
  include_directories(${LIBDL_INCLUDE_DIR})
  list(APPEND PLATFORM_LIBRARIES ${LIBDL_LIBRARIES})

  find_package(Threads REQUIRED)
  list(APPEND PLATFORM_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

elseif(APPLE)
  find_library(COCOA_LIBRARY Cocoa)
  find_library(IOKIT_LIBRARY IOKit)
  find_library(COREVIDEO_LIBRARY CoreVideo)
  find_library(CARBON_LIBRARY Carbon)
  list(APPEND PLATFORM_LIBRARIES ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${CARBON_LIBRARY})
endif()

# Dependencies folder
add_subdirectory(${DEPENDENCIES_DIR})

# Build flags
if(UNIX)
  if(KENGINE_DEBUG_MODE)
    set(CXX_COMPILE_FLAGS "-Wall -g -O0")
  else()
    set(CXX_COMPILE_FLAGS "-O2")
  endif()
elseif(WIN32)
  set(CXX_COMPILE_FLAGS "/wd4068")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_COMPILE_FLAGS}")

# Engine source
add_subdirectory(src)

# Examples. Optional folder. No more hard failure if missing.
if(BUILD_KENGINE_EXAMPLES)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt")
    add_subdirectory(examples)
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nikte/CMakeLists.txt")
    add_subdirectory(nikte)
  else()
    message(STATUS "Examples enabled, but no examples folder found. Skipping.")
  endif()
endif()

# Tests
if(BUILD_KENGINE_TESTS)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")
    add_subdirectory(test)
  else()
    message(STATUS "Tests enabled, but test folder is missing. Skipping.")
  endif()
endif()
