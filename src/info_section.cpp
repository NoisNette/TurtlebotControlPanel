#include "turtlebot_control_panel/info_section.hpp"

namespace turtlebot_control_panel {
    InfoSection::InfoSection(QWidget *parent) : QGroupBox("ℹ️ | Info", parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        cmdVelLabel_ = new QLabel("/cmd_vel : None");
        layout->addWidget(cmdVelLabel_);

        setLayout(layout);
    }

    void InfoSection::updateCmdVel_(const geometry_msgs::msg::Twist::SharedPtr msg) const {
        double lin = msg->linear.x;
        double ang = msg->angular.z;
        cmdVelLabel_->setText(("cmd_vel : " + std::to_string(lin) + ", " + std::to_string(ang)).c_str());
    }
}