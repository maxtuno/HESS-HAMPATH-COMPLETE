cmake_minimum_required(VERSION 2.8.12)
project(libhess C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)

add_library(hess SHARED src/hess.cc include/hess/hess.hh)