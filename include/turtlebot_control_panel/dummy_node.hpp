#ifndef DUMMY_NODE_H
#define DUMMY_NODE_H

#include <rclcpp/rclcpp.hpp>

namespace turtlebot_control_panel {
  class DummyNode : public rclcpp::Node {
    public:
      DummyNode(std::string node_name) : Node(node_name) {};
      ~DummyNode() {};
  };
}

#endif