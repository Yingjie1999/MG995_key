cmake_minimum_required(VERSION 2.8.3)
project(mg995_control)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Eigen3 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES MG995_control
   CATKIN_DEPENDS roscpp std_msgs geometry_msgs
#  DEPENDS system_lib
)

include_directories(
        include
  ${catkin_INCLUDE_DIRS}
)

add_executable(MG995_control_node
        src/MG995_control_node.cpp
        src/MG995RosDriver.cpp
        src/MG995SerialHardware.cpp
        src/BoostSerialCommunicator.cpp
        src/utils.cpp)

target_link_libraries(MG995_control_node
        ${catkin_LIBRARIES}
        )
