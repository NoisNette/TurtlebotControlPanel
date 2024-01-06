#include "turtlebot_control_panel/turtlebot_control_panel.hpp"

namespace turtlebot_control_panel {
    TurtlebotControlPanel::TurtlebotControlPanel(QWidget* parent) : rviz_common::Panel(parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        localizationSection_ = new LocalizationSection(this);
        layout->addWidget(localizationSection_);

        infoSection_ = new InfoSection(this);
        layout->addWidget(infoSection_);

        teleopSection_ = new TeleopSection(this);
        layout->addWidget(teleopSection_);

        setLayout(layout);
    }

    void TurtlebotControlPanel::save(rviz_common::Config config) const {
        rviz_common::Panel::save(config);
    }

    void TurtlebotControlPanel::load(const rviz_common::Config& config) {
        rviz_common::Panel::load(config);
    }

    void TurtlebotControlPanel::onInitialize() {
        auto rviz_ros_node = this->getDisplayContext()->getRosNodeAbstraction().lock()->get_raw_node();

        this->cmdVelSubscription_ = rviz_ros_node->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            1,
            [this](const geometry_msgs::msg::Twist::SharedPtr msg) { infoSection_->updateCmdVel_(msg); }
        );
    }
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(turtlebot_control_panel::TurtlebotControlPanel, rviz_common::Panel)