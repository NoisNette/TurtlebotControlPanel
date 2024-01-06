cmake_minimum_required(VERSION 3.8)
project(turtlebot_control_panel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(pluginlib REQUIRED)
find_package(geometry_msgs REQUIRED)

set(${PROJECT_NAME}_headers_to_moc
  include/${PROJECT_NAME}/turtlebot_control_panel.hpp
  include/${PROJECT_NAME}/dummy_node.hpp
  include/${PROJECT_NAME}/localization_section.hpp
  include/${PROJECT_NAME}/info_section.hpp
  include/${PROJECT_NAME}/teleop_section.hpp
  # include/${PROJECT_NAME}/cmd_vel_subscriber_node.hpp
)

foreach(header "${${PROJECT_NAME}_headers_to_moc}")
  qt5_wrap_cpp(${PROJECT_NAME}_moc_files "${header}")
endforeach()

set(${PROJECT_NAME}_source_files
  src/turtlebot_control_panel.cpp
  src/localization_section.cpp
  src/info_section.cpp
  src/teleop_section.cpp
  src/cmd_vel_subscriber_node.cpp
  # src/node_runner.cpp
)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_moc_files}
  ${${PROJECT_NAME}_source_files}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_export_include_directories(include)
ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rviz_common
  sensor_msgs
  spatz_interfaces
  rviz_ogre_vendor
)

add_executable(cmd_vel_subscriber_node src/cmd_vel_subscriber_node.cpp)
# add_executable(node_runner src/node_runner.cpp)

# Link ament packages
ament_target_dependencies(${PROJECT_NAME} rclcpp rviz_common rviz_rendering geometry_msgs)
# ament_target_dependencies(node_runner rclcpp rviz_common)
ament_target_dependencies(cmd_vel_subscriber_node rclcpp rviz_common geometry_msgs)

# Link non ament packages
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${PROJECT_NAME} PRIVATE "${PROJECT_NAME}_BUILDING_LIBRARY")

# prevent pluginlib from using boost
target_compile_definitions(${PROJECT_NAME} PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch rviz
  DESTINATION share/${PROJECT_NAME}/
)

# install(TARGETS node_runner
#   DESTINATION lib/${PROJECT_NAME}
# )

install(TARGETS cmd_vel_subscriber_node
  DESTINATION lib/${PROJECT_NAME}
)

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY include/
  DESTINATION include
)

set(BUILD_TESTING false)
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

ament_package()
