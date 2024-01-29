cmake_minimum_required(VERSION 3.26.0 )

project(hhgeometry  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PUBLIC
  hhgeometry.hpp
PRIVATE
  hhgeometry.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)






