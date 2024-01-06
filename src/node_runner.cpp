// #include <src/cmd_vel_subscriber_node.cpp>
#include </home/david-lt/rviz2_ws/src/turtlebot_control_panel/src/cmd_vel_subscriber_node.cpp>


int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<turtlebot_control_panel::CmdVelSubscriberNode>());
    rclcpp::shutdown();
}