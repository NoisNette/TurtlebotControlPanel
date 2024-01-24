#ifndef LOCALIZATION_SECTION_H
#define LOCALIZATION_SECTION_H

#include <rclcpp/rclcpp.hpp>
#include <rviz_common/display.hpp>
#include <rviz_common/display_group.hpp>

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>

#include <array>
#include <stdexcept>
#include <memory>

namespace turtlebot_control_panel {
  class LocalizationSection : public QGroupBox {
    Q_OBJECT
    public:
      LocalizationSection(
        QWidget *parent,
        rviz_common::DisplayGroup *displayGroup
      );

    private:
      QPushButton* startLocalizationButton_;
      QPushButton* stopLocalizationButton_;
      QPushButton* saveMapButton_;


      bool localizationRunning_ = false;
      
      void startLocalization_();
      void stopLocalization_();
      void saveMap_();

      void findAndTerminateProcess(std::string name);
  };
}

#endif