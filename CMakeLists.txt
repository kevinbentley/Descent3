cmake_minimum_required(VERSION 3.20)  # For using CMAKE_<LANG>_BYTE_ORDER

# set default cmake build type to Debug (None Debug Release RelWithDebInfo MinSizeRel)
if(NOT CMAKE_BUILD_TYPE AND NOT DEFINED ENV{CMAKE_BUILD_TYPE})
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "default build type")
endif()

project(Descent3
  LANGUAGES C CXX
  VERSION 1.5.0
)

option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored compiler warnings/errors (GCC/Clang only; esp. useful with ninja)." OFF)
option(FORCE_PORTABLE_INSTALL "Install all files into local directory defined by CMAKE_INSTALL_PREFIX" ON)
option(ENABLE_LOGGER "Enable logging to the terminal" OFF)
option(ENABLE_MEM_RTL "Enable Real-time library memory management functions (disable to verbose memory allocations)" ON)
option(BUILD_TESTING "Enable testing. Requires GTest." OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  option(BUILD_EDITOR "Build internal editor" OFF)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(FORCE_COLORED_OUTPUT)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    set(CMAKE_COLOR_DIAGNOSTICS ON)
  else()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      add_compile_options(-fdiagnostics-color=always)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      add_compile_options(-fcolor-diagnostics)
    endif()
  endif()
endif()

include(GNUInstallDirs)
if(FORCE_PORTABLE_INSTALL)
  set(CMAKE_INSTALL_BINDIR ".")
  set(CMAKE_INSTALL_LIBDIR ".")
  set(CMAKE_INSTALL_DATADIR ".")
  set(CMAKE_INSTALL_DOCDIR ".")
endif()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "Default install path" FORCE)
endif()

if(CMAKE_CXX_BYTE_ORDER STREQUAL "BIG_ENDIAN")
  message(STATUS "Big Endian system detected.")
  add_compile_definitions("OUTRAGE_BIG_ENDIAN")
endif()


# 64 bit machines have a different game checksum than 32 bit machines
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  add_definitions(-DCHECKSUM=2273889835UL)
else()
  add_definitions(-DCHECKSUM=2273873307UL)
endif()

if(BUILD_TESTING)
  find_package(GTest REQUIRED)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(tests)
endif()

# rebuild d3_version.h every time
add_custom_target(get_git_hash ALL)

add_custom_command(
  TARGET get_git_hash
  COMMAND ${CMAKE_COMMAND}
    -D SOURCE_DIR=${PROJECT_SOURCE_DIR}
    -D TARGET_DIR=${PROJECT_BINARY_DIR}
    -D PROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -D PROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -D PROJECT_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -P ${PROJECT_SOURCE_DIR}/cmake/CheckGit.cmake
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

install(
  FILES LICENSE README.md THIRD_PARTY.md
  DESTINATION ${CMAKE_INSTALL_DOCDIR}
)

if(UNIX)
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-Wno-multichar;${BITS};${EXTRA_CXX_FLAGS}>")
  add_compile_options("$<$<COMPILE_LANGUAGE:C>:${BITS}>")

  find_package(SDL2 REQUIRED)
  # Some versions of the SDL2 find_package set SDL2_INCLUDE_DIR and some set a plural SDL2_INCLUDE_DIRS. Check both.
  message("SDL2 Include Dir is ${SDL2_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS}")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message("Building for Linux")
  add_compile_definitions(__LINUX__ _USE_OGL_ACTIVE_TEXTURES PRIMARY_HOG=\"d3-linux.hog\")
  set(PLATFORM_INCLUDES "lib/linux" ${SDL2_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  message("Building for MAC OSX")
  add_compile_definitions(__LINUX__ MACOSX=1 _USE_OGL_ACTIVE_TEXTURES PRIMARY_HOG=\"d3-osx.hog\")
  set(PLATFORM_INCLUDES "lib/linux" ${SDL2_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # Windows.h defines to avoid as many issues as possible.
  add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX NODRAWTEXT NOBITMAP NOMCX NOSERVICE PRIMARY_HOG=\"d3-win.hog\"
          #[[NOGDI]] # We need GDI for now, enable when GDI is actually not needed (or when all windows.h mentions are gone)
  )

  list(APPEND CMAKE_LIBRARY_PATH "lib/win" "lib/win/DirectX/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}")
  add_compile_options("$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:/EHsc;/RTC1;/W3;/nologo;/c;/Zi;/TP;/errorReport:prompt>")
  add_compile_options("$<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:/GL;/FD;/EHsc;/W3;/nologo;/c;/Zi;/TP;/errorReport:prompt>")

  string(APPEND CMAKE_EXE_LINKER_FLAGS " /SAFESEH:NO /NODEFAULTLIB:LIBC")
  set(CMAKE_MODULE_LINKER_FLAGS "/SAFESEH:NO /NODEFAULTLIB:LIBC")
  add_compile_definitions(IS_WINDOWS _CRT_SECURE_NO_WARNINGS WIN32 _CRT_SECURE_NO_WARNINGS _CRT_SECURE_NO_DEPRECATE _CRT_NONSTDC_NO_DEPRECATE)

  set(PLATFORM_INCLUDES "lib/win/DirectX" "lib/win")

  set(CMAKE_FIND_LIBRARY_PREFIXES "")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

  add_compile_definitions(DIRECTINPUT_VERSION=0x0500)
  find_library(DSOUND_LIBRARY NAMES dsound REQUIRED)
  find_library(DINPUT_LIBRARY NAMES dinput REQUIRED)
  find_library(DXGUID_LIBRARY NAMES dxguid REQUIRED)
  find_library(DDRAW_LIBRARY NAMES ddraw REQUIRED)

  if(MSVC AND CMAKE_CXX_SIMULATE_ID STREQUAL "")
    add_compile_options("/we4150")  # deletion of pointer to incomplete type 'type'; no destructor called
#    add_compile_options("/we4305")  # truncation from 'X' to 'Y'
    add_compile_options("/we4474")  # too many arguments passed for format string
    add_compile_options("/we4700")  # uninitialized local variable 'X' used
    add_compile_options("/we4804")  # unsafe use of type 'bool' in operation
    add_compile_options("/we4806")  # unsafe operation: no value of type 'bool' promoted to type 'int' can equal the given constant
    add_compile_options("/we4473")  # not enough arguments passed for format string
    add_compile_options("/we4477")  # format string requires argument of type X but variadic argument Y has type Z
    add_compile_options("/we4715")  # 'function' : not all control paths return a value
    add_compile_options("/we4834")  # discarding return value of function with [[nodiscard]] attribute
  endif()

  add_compile_options("/MP")  # so msbuild builds with multiple processes
endif()

add_compile_definitions($<$<CONFIG:Release>:RELEASE>)
add_compile_definitions($<$<CONFIG:Debug>:_DEBUG>)

find_package(ZLIB REQUIRED)

if(ENABLE_LOGGER)
  message("Enabling Logging")
  add_compile_definitions(LOGGER)
endif()

include_directories(
  "cfile"   # TODO: Remove after untying all modules
  "ddebug"  # -*-
  "fix"     # -*-
  "lib"     # TODO: Remove after untying all modules
  "linux"   # -*-
  "Descent3"
  ${PLATFORM_INCLUDES}
)

add_subdirectory(third_party)

add_subdirectory(2dlib)
add_subdirectory(AudioEncode)
add_subdirectory(bitmap)
add_subdirectory(cfile)
add_subdirectory(czip)
add_subdirectory(d3music)
add_subdirectory(ddebug)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_subdirectory(dd_grwin32)
  add_subdirectory(win32)
else()
  add_subdirectory(linux)
endif()

add_subdirectory(ddio)
add_subdirectory(dd_video)
add_subdirectory(fix)
add_subdirectory(manage)
add_subdirectory(grtext)
add_subdirectory(mem)
add_subdirectory(misc)
add_subdirectory(model)
add_subdirectory(module)
add_subdirectory(movie)
add_subdirectory(music)
add_subdirectory(networking)
add_subdirectory(physics)
add_subdirectory(renderer)
add_subdirectory(rtperformance)
add_subdirectory(sndlib)
add_subdirectory(stream_audio)
add_subdirectory(ui)
add_subdirectory(unzip)
add_subdirectory(vecmat)
add_subdirectory(libmve)
add_subdirectory(md5)
add_subdirectory(libacm)


if(BUILD_EDITOR AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_subdirectory(editor)
endif()

add_subdirectory(Descent3)

add_subdirectory(tools)
add_subdirectory(netcon)
add_subdirectory(netgames)
add_subdirectory(scripts)
