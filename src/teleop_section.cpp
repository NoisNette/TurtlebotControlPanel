#include "turtlebot_control_panel/teleop_section.hpp"

namespace turtlebot_control_panel {
    TeleopSection::TeleopSection(QWidget *parent) : QGroupBox("🕹️ | Teleop", parent), linearVelocity_(0.5), angularVelocity_(0.5) {
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
        linearVelocityEditor_ = new QDoubleSpinBox;
        linearVelocityEditor_->setRange(0, 1.0);
        linearVelocityEditor_->setValue(linearVelocity_);
        linearVelocityEditor_->setSingleStep(0.1);
        rowLayout->addWidget(linearVelocityEditor_);
        rowLayout->addWidget(new QLabel("Angular Velocity: "));
        angularVelocityEditor_ = new QDoubleSpinBox;
        angularVelocityEditor_->setRange(0, 1.0);
        angularVelocityEditor_->setValue(linearVelocity_);
        angularVelocityEditor_->setSingleStep(0.1);
        rowLayout->addWidget(angularVelocityEditor_);
        layout->addLayout(rowLayout);

        QGridLayout* gridLayout = new QGridLayout;

        forwardBtn_ = new QPushButton("↑");
        backwardBtn_ = new QPushButton("↓");
        leftBtn_ = new QPushButton("↶");
        rightBtn_ = new QPushButton("↷");

        gridLayout->addWidget(forwardBtn_, 0, 1);
        gridLayout->addWidget(backwardBtn_, 2, 1);
        gridLayout->addWidget(leftBtn_, 1, 0);
        gridLayout->addWidget(rightBtn_, 1, 2);

        layout->addLayout(gridLayout);

        setLayout(layout);

        connect(outputTopicEditor_, SIGNAL(editingFinished()), this, SLOT(updateTopic()));
        connect(linearVelocityEditor_, SIGNAL(valueChanged(double)), this, SLOT(updateLinearVelocity(double)));
        connect(angularVelocityEditor_, SIGNAL(valueChanged(double)), this, SLOT(updateAngularVelocity(double)));

        connect(forwardBtn_, &QPushButton::pressed, [this](void) { sendVel('f'); });
        connect(backwardBtn_, &QPushButton::pressed, [this](void) { sendVel('b'); });
        connect(leftBtn_, &QPushButton::pressed, [this](void) { sendVel('l'); });
        connect(rightBtn_, &QPushButton::pressed, [this](void) { sendVel('r'); });

        connect(forwardBtn_, &QPushButton::released, [this](void) { sendVel('s'); });
        connect(backwardBtn_, &QPushButton::released, [this](void) { sendVel('s'); });
        connect(leftBtn_, &QPushButton::released, [this](void) { sendVel('s'); });
        connect(rightBtn_, &QPushButton::released, [this](void) { sendVel('s'); });
    }

    void TeleopSection::setTopic(const QString& topic) {
        if (topic == outputTopic_)
            return;

        outputTopic_ = topic;

        publisher_ = dummy_node_->create_publisher<geometry_msgs::msg::Twist>(
            outputTopic_.toStdString(),
            1
        );
    }

    void TeleopSection::sendVel(char dir) {
        if (!publisher_)
            return;

        double linear, angular;
        switch (dir) {
            case 'f':
                linear = linearVelocity_;
                break;
            case 'b':
                linear = -linearVelocity_;
                break;
            case 'l':
                angular = angularVelocity_;
                break;
            case 'r':
                angular = -angularVelocity_;
                break;
            case 's':
                linear = 0;
                angular = 0;
                break;
        }

        geometry_msgs::msg::Twist msg;
        msg.linear.x = linear;
        msg.linear.y = 0;
        msg.linear.z = 0;
        msg.angular.x = 0;
        msg.angular.y = 0;
        msg.angular.z = angular;
        publisher_->publish(msg);
    }

    void TeleopSection::updateLinearVelocity(double value) {
        linearVelocity_ = value;
    }

    void TeleopSection::updateAngularVelocity(double value) {
        angularVelocity_ = value;
    }

    void TeleopSection::updateTopic() {
        setTopic(outputTopicEditor_->text());
    }
}