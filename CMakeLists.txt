cmake_minimum_required(VERSION 3.26.0 )

project(hh  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(hhgeometry)

set(BUILD_HHTEST OFF)  #<===============================================

if(BUILD_HHTEST)
  add_executable(hhtest)
  target_sources(hhtest
    PUBLIC
      test.cpp
  )
  target_link_libraries(hhtest 
    PUBLIC
      hhgeometry)
else()
  add_executable(hhmain)
  target_sources(hhmain
    PUBLIC
      main.cpp
  )
    target_link_libraries(hhmain 
    PUBLIC
      hhgeometry)
endif()





