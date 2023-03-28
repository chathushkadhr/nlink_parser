#include "nlink_parser/linktrack/protocols/nlt_anchorframe0.h"

NLT_ProtocolAnchorFrame0::NLT_ProtocolAnchorFrame0(rclcpp::Node *node)
    : NLinkProtocol(
          true, nlt_anchorframe0_.fixed_part_size,
          {nlt_anchorframe0_.frame_header, nlt_anchorframe0_.function_mark},
          {nlt_anchorframe0_.tail_check}),
      publisher_(nullptr),
      node_(node),
      topic("nlink_linktrack_anchorframe0"),
      logger_(rclcpp::get_logger("NLT_ProtocolAnchorFrame0")),
      clock_(rclcpp::Clock())
{
  if (node_!=nullptr)
    logger_ = node_->get_logger();
}

bool NLT_ProtocolAnchorFrame0::Verify(const uint8_t *data)
{
  return data[length() - 1] == nlt_anchorframe0_.tail_check;
}

void NLT_ProtocolAnchorFrame0::HandleData(const uint8_t *serial_data)
{
  
  if (node_==nullptr){
    RCLCPP_ERROR_THROTTLE(logger_, clock_, 1.0 , "Node is a null pointer");
    return;
  }

  nlink_parser::msg::LinktrackAnchorframe0 g_msg_anchorframe0;
  nlt_anchorframe0_.UnpackData(serial_data, length());

  if (publisher_==nullptr){
    publisher_ = node_->create_publisher<nlink_parser::msg::LinktrackAnchorframe0>(topic, 200);
    RCLCPP_INFO_STREAM( node_->get_logger() , 
    std::string(topic) << " has been advertised,use 'ros2 topic echo " << 
    std::string(topic) << "' to view the data");
  }
  auto data = nlt_anchorframe0_.result;
  g_msg_anchorframe0.role = data.role;
  g_msg_anchorframe0.id = data.id;
  g_msg_anchorframe0.voltage = data.voltage;
  g_msg_anchorframe0.local_time = data.local_time;
  g_msg_anchorframe0.system_time = data.system_time;
  auto &msg_nodes = g_msg_anchorframe0.nodes;
  msg_nodes.clear();
  decltype(g_msg_anchorframe0.nodes)::value_type msg_node;
  for (size_t i = 0, icount = data.valid_node_count; i < icount; ++i)
  {
    auto node = data.nodes[i];
    msg_node.role = node->role;
    msg_node.id = node->id;
    ARRAY_ASSIGN(msg_node.pos_3d, node->pos_3d)
    ARRAY_ASSIGN(msg_node.dis_arr, node->dis_arr)
    msg_nodes.push_back(msg_node);
  }
  
  publisher_->publish(g_msg_anchorframe0); 
}    

