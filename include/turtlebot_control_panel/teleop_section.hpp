#ifndef TELEOP_SECTION_H
#define TELEOP_SECTION_H

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include "turtlebot_control_panel/dummy_node.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QString>
#include <QPushButton>
#include <QDoubleSpinBox>

using std::placeholders::_1;

namespace turtlebot_control_panel {
  class TeleopSection : public QGroupBox {
    Q_OBJECT
    public:
      TeleopSection(QWidget *parent = 0);

    protected Q_SLOTS:
      void sendVel(char dir);
      void updateLinearVelocity(double value);
      void updateAngularVelocity(double value);
      void updateTopic();

    private:
      std::shared_ptr<DummyNode> dummy_node_;
      rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

      QLineEdit* outputTopicEditor_;
      QString outputTopic_;

      QDoubleSpinBox* linearVelocityEditor_;
      QDoubleSpinBox* angularVelocityEditor_;

      QPushButton* forwardBtn_;
      QPushButton* backwardBtn_;
      QPushButton* leftBtn_;
      QPushButton* rightBtn_;

      float linearVelocity_;
      float angularVelocity_;

      void setTopic(const QString& topic);
  };
}

#endif