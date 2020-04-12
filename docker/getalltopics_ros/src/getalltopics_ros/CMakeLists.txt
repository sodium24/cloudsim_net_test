cmake_minimum_required(VERSION 3.5.1)
project(getalltopics_ros)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
endif()

find_package(catkin REQUIRED
  COMPONENTS
    roscpp
)

find_package(ignition-common3 REQUIRED)
find_package(ignition-math6 REQUIRED)
find_package(ignition-msgs4 REQUIRED)
find_package(ignition-transport7 REQUIRED)

catkin_package(
  CATKIN_DEPENDS roscpp
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${ignition-transport7_INCLUDE_DIRS}
  ${ignition-msgs4_INCLUDE_DIRS}
  ${ignition-common3_INCLUDE_DIRS}
)

link_directories()

set(project_libs
  ${catkin_LIBRARIES}
  ${ignition-transport7_LIBRARIES}
  ${ignition-msgs4_LIBRARIES}
  ${ignition-common3_LIBRARIES}
)

add_executable(getalltopics src/getalltopics.cpp)
target_link_libraries(getalltopics ${project_libs})

install(TARGETS getalltopics
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

