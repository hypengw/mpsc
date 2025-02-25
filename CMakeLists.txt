cmake_minimum_required(VERSION 3.28)
project(
  mpsc
  VERSION 1.0
  DESCRIPTION "Multi-Producer Single Consumer Queue Implementation"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# parking
find_package(parking QUIET)
if(NOT parking_FOUND)
  message(STATUS "parking not found, fetching it...")
  FetchContent_Declare(
    parking
    GIT_REPOSITORY https://github.com/hypengw/parking.git
    GIT_TAG b5c4c564f1a1597d3ca23003043bd4b8fffc2fe6
    GIT_SHALLOW 1
    EXCLUDE_FROM_ALL)
  FetchContent_MakeAvailable(parking)
endif()

add_library(mpsc)
add_library(mpsc::mpsc ALIAS mpsc)
target_sources(
  mpsc
  PUBLIC FILE_SET
         all
         TYPE
         CXX_MODULES
         FILES
         src/mpmc/utils/cache_padded.cppm
         src/mpmc/context.cppm
         src/mpmc/waker.cppm
         src/mpmc/array.cppm
         src/mpmc/counter.cppm
         src/mpmc/mod.cppm
         src/mpsc.cppm)
target_link_libraries(mpsc PUBLIC parking::parking)

# Add installation rules
if(PROJECT_IS_TOP_LEVEL)
  include(GNUInstallDirs)
  install(
    TARGETS mpsc
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

# Testing configuration
if(PROJECT_IS_TOP_LEVEL)

  add_subdirectory(test)
endif()
