#include "turtlebot_control_panel/localization_section.hpp"
#include <iostream>

namespace turtlebot_control_panel {
    LocalizationSection::LocalizationSection(QWidget *parent) : QGroupBox("🗺️ | Localization", parent) {
        QVBoxLayout* layout = new QVBoxLayout;

        QHBoxLayout* startStopLayout = new QHBoxLayout;

        startLocalizationButton_ = new QPushButton("Start");
        stopLocalizationButton_ = new QPushButton("Stop");
        saveMapButton_ = new QPushButton("Save Map");

        startStopLayout->addWidget(startLocalizationButton_);
        startStopLayout->addWidget(stopLocalizationButton_);

        layout->addLayout(startStopLayout);
        layout->addWidget(saveMapButton_);

        setLayout(layout);

        connect(startLocalizationButton_, &QPushButton::clicked, [this](void) { startLocalization_(); });
        connect(stopLocalizationButton_, &QPushButton::clicked, [this](void) { stopLocalization_(); });
        connect(saveMapButton_, &QPushButton::clicked, [this](void) { saveMap_(); });
    }

    void LocalizationSection::startLocalization_() {
        std::cout << "Start\n";
        system("ros2 launch turtlebot3_cartographer cartographer.launch.py");
    }

    void LocalizationSection::stopLocalization_() {
        std::cout << "Stop\n";
    }

    void LocalizationSection::saveMap_() {
        std::cout << "Save\n";
        QString dir = QFileDialog::getExistingDirectory(this, tr("Save Map"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (dir == "")
            return;

        std::string command = "ros2 run nav2_map_server map_saver_cli -f " + dir.toStdString() + "/map";
        system(command.c_str());
    }
}