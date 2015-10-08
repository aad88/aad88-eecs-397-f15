cmake_minimum_required(VERSION 2.8.3)
project(defiore_action_pkg)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  catkin_simple
  roscpp
)

find_package(Boost REQUIRED COMPONENTS system thread)
catkin_simple()

#Executables
cs_add_executable(action_server src/action_server.cpp)
cs_add_executable(action_client src/action_client.cpp)

cs_install()
cs_export()
