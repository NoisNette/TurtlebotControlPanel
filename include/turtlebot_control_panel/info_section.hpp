#ifndef INFO_SECTION_H
#define INFO_SECTION_H

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

namespace turtlebot_control_panel {
  class InfoSection : public QGroupBox {
    Q_OBJECT
    public:
      InfoSection(QWidget *parent = 0);
      void updateCmdVel_(const geometry_msgs::msg::Twist::SharedPtr msg) const;

    private:
      QLabel* cmdVelLabel_;

      void cmdVelCallback_(const geometry_msgs::msg::Twist & msg) const;
  };
}

#endif