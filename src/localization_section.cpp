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
        system("ros2 launch turtlebot_control_panel no_rviz.launch.py &");
    }

    void LocalizationSection::stopLocalization_() {
        std::cout << "Stop\n";
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("ps -aux | grep turtlebot3_cartographer", "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed...");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        int i = 0;
        bool gotSpace = false;
        while (!gotSpace && i < (int)result.length()) {
            i += 1;
            if (result[i] == ' ')
                gotSpace = true;
            else if (gotSpace)
                break;
        }
        // stopLocalizationButton_->setText(std::to_string(i).c_str());
        
        int spaceIdx = result.find(" ", i);
        std::string pid = result.substr(i, i+spaceIdx);
        int len = (int) result.length();
        stopLocalizationButton_->setText(std::to_string(len).c_str());
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