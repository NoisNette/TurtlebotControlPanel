#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
// #include <rviz_common/displays_panel.hpp>
// #include </home/david-lt/rviz2_ws/src/rviz/rviz_common/src/rviz_common/displays_panel.hpp>

using std::placeholders::_1;

namespace turtlebot_control_panel {
    class CmdVelSubscriberNode : public rclcpp::Node {
        public:
            CmdVelSubscriberNode() : Node("cmd_vel_subscriber") {
                subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
                    "/cmd_vel",
                    rclcpp::SystemDefaultsQoS(),
                    std::bind(&CmdVelSubscriberNode::nodeCallback_, this, _1)
                );
            }

        private:
            rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
            void nodeCallback_(const geometry_msgs::msg::Twist::SharedPtr msg) const {
                RCLCPP_INFO(this->get_logger(), "Recieved - Linear Velocity : '%f', Angular Velocity : '%f'", msg->linear.x, msg->angular.z);
                // rviz_common::DisplaysPanel::onNewDisplay();
            }
    };
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<turtlebot_control_panel::CmdVelSubscriberNode>());
    rclcpp::shutdown();
}