cmake_minimum_required(VERSION 2.8)

project(UbiGaCha9)

set(
  CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake_modules"
  "/usr/local/share/SFML/cmake/Modules/"
  ${CMAKE_MODULE_PATH}
  )

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")

find_package(SFML 2.1 COMPONENTS system window graphics audio network REQUIRED)

include_directories(
  include
  ${SFML_INCLUDE_DIR}
  )

file(
  GLOB_RECURSE
  PROJECT_SOURCES
  src/*.cpp
  src/SfTileEngine/*.cpp
  src/TinyXML/*.cpp
  )

file(
  GLOB_RECURSE
  PROJECT_HEAUDERS
  include/*.hh
  )

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

file(COPY ${PROJECT_SOURCE_DIR}/ressource DESTINATION ${PROJECT_BINARY_DIR})
