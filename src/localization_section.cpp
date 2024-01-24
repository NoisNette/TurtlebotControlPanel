#include "turtlebot_control_panel/localization_section.hpp"

namespace turtlebot_control_panel {
    LocalizationSection::LocalizationSection(
            QWidget *parent,
            rviz_common::DisplayGroup *displayGroup
        ) : QGroupBox("🗺️ | Localization", parent) {
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
        if (localizationRunning_)
            return;
        localizationRunning_ = true;
        system("ros2 launch turtlebot_control_panel cartographer.launch.py &");
    }

    void LocalizationSection::stopLocalization_() {
        if (!localizationRunning_)
            return;
        localizationRunning_ = false;

        findAndTerminateProcess("turtlebot3_cartographer");
        findAndTerminateProcess("cartographer_occupancy_grid_node");
    }

    void LocalizationSection::saveMap_() {
        if (!localizationRunning_)
            return;
            
        QString dir = QFileDialog::getExistingDirectory(this, tr("Save Map"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (dir == "")
            return;

        std::string command = "ros2 run nav2_map_server map_saver_cli -f " + dir.toStdString() + "/map";
        system(command.c_str());
    }

    void LocalizationSection::findAndTerminateProcess(std::string name) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(("ps -aux | grep " + name).c_str(), "r"), pclose);
        if (!pipe)
            throw std::runtime_error("popen() failed...");
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            result += buffer.data();

        int i = 0;
        bool gotSpace = false;
        while (i < (int)result.length()) {
            if (result[i] == ' ')
                gotSpace = true;
            else if (gotSpace)
                break;
            i += 1;
        }        
        std::string pid = result.substr(i, result.find(" ", i)-i);
        system(("kill " + pid).c_str());
    }
}