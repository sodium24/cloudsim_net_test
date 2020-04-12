cmake_minimum_required(VERSION 3.5.1)
project(advertisetopics)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
endif()

find_package(ignition-common3 REQUIRED)
find_package(ignition-math6 REQUIRED)
find_package(ignition-msgs4 REQUIRED)
find_package(ignition-transport7 REQUIRED)

include_directories(
  ${ignition-transport7_INCLUDE_DIRS}
  ${ignition-msgs4_INCLUDE_DIRS}
  ${ignition-common3_INCLUDE_DIRS}
)

link_directories()

set(project_libs
  ${ignition-transport7_LIBRARIES}
  ${ignition-msgs4_LIBRARIES}
  ${ignition-common3_LIBRARIES}
)

add_executable(advertisetopics src/advertisetopics.cpp)
target_link_libraries(advertisetopics ${project_libs})

install(TARGETS advertisetopics
  RUNTIME DESTINATION bin
)

