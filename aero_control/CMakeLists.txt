cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#add dynamic reconfigure api
rosbuild_find_ros_package(dynamic_reconfigure)
include(${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake)
gencfg()

include_directories(${Eigen_INCLUDE_DIRS})
rosbuild_add_library(pidcontrol src/pid_control.cpp)



#Testers
rosbuild_add_executable(test_arm_control src/testers/test_arm_control.cpp )
rosbuild_add_executable(test_base_servo src/testers/test_base_servo.cpp )

#Nodes
rosbuild_add_executable(arm_controller src/nodes/arm_controller.cpp )
rosbuild_add_executable(arm_position_control src/nodes/arm_position_control.cpp )
rosbuild_add_executable(base_servo_control src/nodes/base_servo_control.cpp )
rosbuild_add_executable(boom_controller src/nodes/boom_controller.cpp )

rosbuild_add_executable(object_to_pose src/nodes/object_to_pose.cpp )

target_link_libraries(arm_position_control pidcontrol)
target_link_libraries(base_servo_control pidcontrol)


