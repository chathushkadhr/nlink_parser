cmake_minimum_required(VERSION 3.8)
project(nlink_parser)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(serial REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)

#add_subdirectory(lib/protocol_extracter)

set(msg_files
  "msg/LinktrackAnchorframe0.msg"
  "msg/LinktrackNode0.msg"
  "msg/LinktrackNode1.msg"
  "msg/LinktrackNode2.msg"
  "msg/LinktrackNodeframe0.msg"
  "msg/LinktrackNodeframe1.msg"
  "msg/LinktrackNodeframe2.msg"
  "msg/LinktrackNodeframe3.msg"
  "msg/LinktrackTag.msg"
  "msg/LinktrackTagframe0.msg"
  "msg/TofsenseCascade.msg"
  "msg/TofsenseFrame0.msg"
  "msg/LinktrackAoaNode0.msg"
  "msg/LinktrackAoaNodeframe0.msg"
  "msg/LinktrackNode4Anchor.msg"
  "msg/LinktrackNode4Tag.msg"
  "msg/LinktrackNodeframe4.msg"
  "msg/LinktrackNode5.msg"
  "msg/LinktrackNodeframe5.msg"
  "msg/LinktrackNode6.msg"
  "msg/LinktrackNodeframe6.msg"
  "msg/TofsenseMFrame0.msg"
  "msg/TofsenseMFrame0Pixel.msg"
  "msg/IotFrame0.msg"
  "msg/IotFrame0Node.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
   ${msg_files}
)

ament_export_dependencies(rosidl_default_runtime)

set(
  DEPENDENCIES
  rclcpp
  std_msgs
  serial
  geometry_msgs
  nav_msgs
  
)

set(nutils "nutils")
add_library(${nutils}
    lib/protocol_extracter/nprotocol_base.cpp
    lib/protocol_extracter/nprotocol_extracter.cpp
    lib/nlink_unpack/nlink_utils.c
    lib/nlink_unpack/nlink_linktrack_anchorframe0.c
    lib/nlink_unpack/nlink_linktrack_tagframe0.c
    lib/nlink_unpack/nlink_linktrack_nodeframe0.c
    lib/nlink_unpack/nlink_linktrack_nodeframe1.c
    lib/nlink_unpack/nlink_linktrack_nodeframe2.c
    lib/nlink_unpack/nlink_linktrack_nodeframe3.c
    lib/nlink_unpack/nlink_linktrack_nodeframe4.c
    lib/nlink_unpack/nlink_linktrack_nodeframe5.c
    lib/nlink_unpack/nlink_linktrack_nodeframe6.c
    lib/nlink_unpack/nlink_tofsense_frame0.c
    lib/nlink_unpack/nlink_tofsensem_frame0.c
    lib/nlink_unpack/nlink_linktrack_aoa_nodeframe0.c
    lib/nlink_unpack/nlink_iot_frame0.c
    lib/nlink_protocol.cpp
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

set(
  executables
  src/linktrack/main.cpp
  src/linktrack/linktrack_driver.cpp
  src/linktrack/protocols/nlt_anchorframe0.cpp
  src/linktrack/protocols/nlt_tagframe0.cpp
  src/linktrack/protocols/nlt_nodeframe0.cpp
  src/linktrack/protocols/nlt_nodeframe1.cpp
  src/linktrack/protocols/nlt_nodeframe2.cpp
  src/linktrack/protocols/nlt_nodeframe3.cpp
  src/linktrack/protocols/nlt_nodeframe4.cpp
  src/linktrack/protocols/nlt_nodeframe5.cpp
  src/linktrack/protocols/nlt_nodeframe6.cpp
)

add_executable(exec_uwb ${executables}) 
add_executable(rviz_uwb src/linktrack/main_rviz src/linktrack/rviz_converter.cpp) 

ament_target_dependencies(exec_uwb ${DEPENDENCIES})
ament_target_dependencies(rviz_uwb ${DEPENDENCIES})

target_include_directories(exec_uwb  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/nlink_unpack>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/protocol_extracter>
   $<INSTALL_INTERFACE:include>)

target_include_directories(rviz_uwb  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/nlink_unpack>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/protocol_extracter>
   $<INSTALL_INTERFACE:include>)

target_compile_features(exec_uwb PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_features(rviz_uwb PUBLIC c_std_99 cxx_std_17)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(exec_uwb "${cpp_typesupport_target}")
target_link_libraries(rviz_uwb "${cpp_typesupport_target}")
target_link_libraries(exec_uwb ${nutils})


install(TARGETS exec_uwb
 DESTINATION lib/${PROJECT_NAME}
 )
install(TARGETS rviz_uwb
DESTINATION lib/${PROJECT_NAME}
)


install(
  DIRECTORY include launch lib
  DESTINATION share/${PROJECT_NAME}
)

install(
  TARGETS ${nutils}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  )

ament_package()
