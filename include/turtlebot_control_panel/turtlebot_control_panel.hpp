#ifndef TURTLEBOT_CONTROL_PANEL_H
#define TURTLEBOT_CONTROL_PANEL_H

#include <rclcpp/rclcpp.hpp>
#include <rviz_common/panel.hpp>

#include <QVBoxLayout>

#include "turtlebot_control_panel/visibility_control.hpp"
#include "turtlebot_control_panel/localization_section.hpp"
#include "turtlebot_control_panel/info_section.hpp"
#include "turtlebot_control_panel/teleop_section.hpp"

namespace turtlebot_control_panel {
    class TurtlebotControlPanel : public rviz_common::Panel {
        Q_OBJECT
        public:
          TurtlebotControlPanel(QWidget* parent = 0);

          virtual void save( rviz_common::Config config ) const;
          virtual void load( const rviz_common::Config& config );
        
        private:
          LocalizationSection* localizationSection_;
          InfoSection* infoSection_;
          TeleopSection* teleopSection_;
    };
}

#endif