#ifndef INFO_SECTION_H
#define INFO_SECTION_H

#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

using std::placeholders::_1;

namespace turtlebot_control_panel {
  class CmdVelSubscriberNode : public rclcpp::Node {
    public:
      CmdVelSubscriberNode();

    private:
      rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;

      void nodeCallback_(const geometry_msgs::msg::Twist::SharedPtr msg) const;
  };
}

#endif