#include "nlink_parser/linktrack/protocols/nlt_nodeframe6.h"

NLT_ProtocolNodeFrame6::NLT_ProtocolNodeFrame6(rclcpp::Node *node)
    : NLinkProtocolVLength(
          true, g_nlt_nodeframe6.fixed_part_size,
          {g_nlt_nodeframe6.frame_header, g_nlt_nodeframe6.function_mark}
          ),
      publisher_(nullptr),
      node_(node),
      topic("nlink_linktrack_nodeframe6"),
      logger_(rclcpp::get_logger("NLT_ProtocolNodeFrame6")),
      clock_(rclcpp::Clock())
{
  if (node_!=nullptr)
    logger_ = node_->get_logger();
}

void NLT_ProtocolNodeFrame6::HandleData(const uint8_t *serial_data)
{
  
  if (node_==nullptr){
    RCLCPP_ERROR_THROTTLE(logger_, clock_, 1.0 , "Node is a null pointer");
    return;
  }

  nlink_parser::msg::LinktrackNodeframe6 g_msg_nodeframe6;
  g_nlt_nodeframe6.UnpackData(serial_data, length());

  if (publisher_==nullptr){
    publisher_ = node_->create_publisher<nlink_parser::msg::LinktrackNodeframe6>(topic, 200);
    RCLCPP_INFO_STREAM( node_->get_logger() , 
    std::string(topic) << " has been advertised,use 'ros2 topic echo " << 
    std::string(topic) << "' to view the data");
  }

  const auto &data = g_nlt_nodeframe6.result;
  auto &msg_data = g_msg_nodeframe6;
  auto &msg_nodes = msg_data.nodes;

  msg_data.role = data.role;
  msg_data.id = data.id;

  msg_nodes.resize(data.valid_node_count);
  for (size_t i = 0; i < data.valid_node_count; ++i)
  {
    auto &msg_node = msg_nodes[i];
    auto node = data.nodes[i];
    msg_node.id = node->id;
    msg_node.role = node->role;
    msg_node.data.resize(node->data_length);
    memcpy(msg_node.data.data(), node->data, node->data_length);
  }
  
  publisher_->publish(msg_data); 
}    

