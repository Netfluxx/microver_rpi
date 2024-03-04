#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class ReceiveNode : public rclcpp::Node {
public:
  ReceiveNode() : Node("receive_node") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "input_topic", 10, std::bind(&ReceiveNode::messageCallback, this, std::placeholders::_1));
  }

private:
  void messageCallback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received: %s", msg->data.c_str());
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ReceiveNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
