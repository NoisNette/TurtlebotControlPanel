#include "turtlebot_control_panel/info_section.hpp"
#include <iostream>

namespace turtlebot_control_panel {
    InfoSection::InfoSection(QWidget *parent) : QGroupBox("Info", parent) {
        dummy_node_ = std::make_shared<DummyNode>("info_dummy_node");

        cmd_vel_sub_ = dummy_node_->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            rclcpp::SystemDefaultsQoS(),
            std::bind(&InfoSection::cmdVelCallback_, this, _1)
        );

        // cmdVelSubscriberNode_ = new CmdVelSubscriberNode();

        QVBoxLayout* layout = new QVBoxLayout;

        cmdVelLabel_ = new QLabel("/cmd_vel : None");
        layout->addWidget(cmdVelLabel_);

        setLayout(layout);
    }

    void InfoSection::cmdVelCallback_(const geometry_msgs::msg::Twist & msg) const {
        // RCLCPP_INFO(dummy_node_->get_logger(), "Recieved - Linear Velocity : '%f', Angular Velocity : '%f'", msg->linear.x, msg->angular.z);
        RCLCPP_INFO(dummy_node_->get_logger(), "Got something...");
        std::cout << "something\n";
    }
}