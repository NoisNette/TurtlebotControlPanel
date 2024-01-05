// #include <memory>

// #include <rclcpp/rclcpp.hpp>
// #include <geometry_msgs/msg/twist.hpp>

// using std::placeholders::_1;

// #include "turtlebot_control_panel/cmd_vel_subscriber_node.hpp"
#include "/home/david/rviz2_ws/src/turtlebot_control_panel/include/turtlebot_control_panel/cmd_vel_subscriber_node.hpp"


// class CmdVelSubscriberNode : public rclcpp::Node {
//     public:
//         CmdVelSubscriberNode() : Node("cmd_vel_subscriber") {
//             subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
//                 "/cmd_vel",
//                 rclcpp::SystemDefaultsQoS(),
//                 std::bind(&CmdVelSubscriberNode::nodeCallback_, this, _1)
//             );
//         }

//     private:
//         rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
//         void nodeCallback_(const geometry_msgs::msg::Twist::SharedPtr msg) const {
//             RCLCPP_INFO(this->get_logger(), "Recieved - Linear Velocity : '%f', Angular Velocity : '%f'", msg->linear.x, msg->angular.z);
//         }
// };

namespace turtlebot_control_panel {
    CmdVelSubscriberNode::CmdVelSubscriberNode() : Node("cmd_vel_subscriber") {
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            rclcpp::SystemDefaultsQoS(),
            std::bind(&CmdVelSubscriberNode::nodeCallback_, this, _1)
        );
    }

    void CmdVelSubscriberNode::nodeCallback_(const geometry_msgs::msg::Twist::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "Recieved - Linear Velocity : '%f', Angular Velocity : '%f'", msg->linear.x, msg->angular.z);
    }
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<turtlebot_control_panel::CmdVelSubscriberNode>());
    rclcpp::shutdown();
}