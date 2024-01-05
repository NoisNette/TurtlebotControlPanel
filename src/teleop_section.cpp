#include "turtlebot_control_panel/teleop_section.hpp"
#include <iostream>

namespace turtlebot_control_panel {
    TeleopSection::TeleopSection(QWidget *parent) : QGroupBox("Teleop", parent), linearVelocity_(0), angularVelocity_(0) {
        dummy_node_ = std::make_shared<DummyNode>("teleop_dummy_node");

        QVBoxLayout* layout = new QVBoxLayout;

        QHBoxLayout* rowLayout = new QHBoxLayout;
        rowLayout->addWidget(new QLabel("Teleop Topic: "));
        outputTopicEditor_ = new QLineEdit("/cmd_vel");
        setTopic("/cmd_vel");
        rowLayout->addWidget(outputTopicEditor_);
        layout->addLayout(rowLayout);

        rowLayout = new QHBoxLayout;
        rowLayout->addWidget(new QLabel("Linear Velocity: "));
        linearVelocityEditor_ = new QLineEdit;
        rowLayout->addWidget(linearVelocityEditor_);
        layout->addLayout(rowLayout);

        rowLayout = new QHBoxLayout;
        rowLayout->addWidget(new QLabel("Angular Velocity: "));
        angularVelocityEditor_ = new QLineEdit;
        rowLayout->addWidget(angularVelocityEditor_);
        layout->addLayout(rowLayout);

        stopButton_ = new QPushButton("Stop");
        layout->addWidget(stopButton_);

        setLayout(layout);

        connect(outputTopicEditor_, SIGNAL(editingFinished()), this, SLOT(updateTopic()));
        connect(linearVelocityEditor_, SIGNAL(editingFinished()), this, SLOT(updateLinearVelocity()));
        connect(angularVelocityEditor_, SIGNAL(editingFinished()), this, SLOT(updateAngularVelocity()));
        connect(stopButton_, &QPushButton::clicked, [this](void) { stopButtonCallback_(); });
    }

    void TeleopSection::setTopic(const QString& topic) {
        if (topic == outputTopic_)
            return;

        outputTopic_ = topic;

        publisher_ = dummy_node_->create_publisher<geometry_msgs::msg::Twist>(
            outputTopic_.toStdString(),
            1
        );

        sendVel();
    }

    void TeleopSection::sendVel() {
        if (!publisher_)
            return;

        geometry_msgs::msg::Twist msg;
        msg.linear.x = linearVelocity_;
        msg.linear.y = 0;
        msg.linear.z = 0;
        msg.angular.x = 0;
        msg.angular.y = 0;
        msg.angular.z = angularVelocity_;
        publisher_->publish(msg);
    }

    void TeleopSection::updateLinearVelocity() {
        try {
            linearVelocity_ = linearVelocityEditor_->text().toFloat();
            std::cout << "New linear velocity: " << linearVelocityEditor_->text().toFloat() << '\n';
        } catch (std::invalid_argument const&) {
            return;
        }
        sendVel();
    }

    void TeleopSection::updateAngularVelocity() {
        try {
            angularVelocity_ = angularVelocityEditor_->text().toFloat();
            std::cout << "New angular velocity: " << angularVelocityEditor_->text().toFloat() << '\n';
        } catch (std::invalid_argument const&) {
            return;
        }
        sendVel();
    }

    void TeleopSection::updateTopic() {
        std::cout << "New Topic: '" << outputTopicEditor_->text().toStdString() << "'\n";
        setTopic(outputTopicEditor_->text());
    }

    void TeleopSection::stopButtonCallback_() {
        linearVelocity_ = 0;
        linearVelocityEditor_->setText("");
        angularVelocity_ = 0;
        angularVelocityEditor_->setText("");
        
        sendVel();
    }
}