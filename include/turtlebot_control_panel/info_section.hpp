#ifndef INFO_SECTION_H
#define INFO_SECTION_H

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include "turtlebot_control_panel/dummy_node.hpp"
// #include "turtlebot_control_panel/cmd_vel_subscriber_node.hpp"
#include "/home/david/rviz2_ws/src/turtlebot_control_panel/include/turtlebot_control_panel/cmd_vel_subscriber_node.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

using std::placeholders::_1;

namespace turtlebot_control_panel {
  class InfoSection : public QGroupBox {
    Q_OBJECT
    public:
      InfoSection(QWidget *parent = 0);

    private:
      std::shared_ptr<DummyNode> dummy_node_;

      // CmdVelSubscriberNode* cmdVelSubscriberNode_;

      rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
      QLabel* cmdVelLabel_;

      void cmdVelCallback_(const geometry_msgs::msg::Twist & msg) const;
  };
}

#endif