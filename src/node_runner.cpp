#include <rclcpp.hpp>

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<turtlebot_control_panel::InfoSection>());
    rclcpp::shutdown();
}