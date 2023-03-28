#include "nlink_parser/linktrack/protocols/nlt_nodeframe4.h"

NLT_ProtocolNodeFrame4::NLT_ProtocolNodeFrame4(rclcpp::Node *node)
    : NLinkProtocolVLength(
          true, g_nlt_nodeframe4.fixed_part_size,
          {g_nlt_nodeframe4.frame_header, g_nlt_nodeframe4.function_mark}
          ),
      publisher_(nullptr),
      node_(node),
      topic("nlink_linktrack_nodeframe4"),
      logger_(rclcpp::get_logger("NLT_ProtocolNodeFrame4")),
      clock_(rclcpp::Clock())
{
  if (node_!=nullptr)
    logger_ = node_->get_logger();
}

void NLT_ProtocolNodeFrame4::HandleData(const uint8_t *serial_data)
{
  
  if (node_==nullptr){
    RCLCPP_ERROR_THROTTLE(logger_, clock_, 1.0 , "Node is a null pointer");
    return;
  }

  nlink_parser::msg::LinktrackNodeframe4 g_msg_nodeframe4;
  g_nlt_nodeframe4.UnpackData(serial_data, length());

  if (publisher_==nullptr){
    publisher_ = node_->create_publisher<nlink_parser::msg::LinktrackNodeframe4>(topic, 200);
    RCLCPP_INFO_STREAM( node_->get_logger() , 
    std::string(topic) << " has been advertised,use 'ros2 topic echo " << 
    std::string(topic) << "' to view the data");
  }

  const auto &data = g_nlt_nodeframe4.result;
  auto &msg_data = g_msg_nodeframe4;
  msg_data.role = data.role;
  msg_data.id = data.id;
  msg_data.local_time = data.local_time;
  msg_data.system_time = data.system_time;
  msg_data.voltage = data.voltage;
  msg_data.tags.resize(data.tag_count);
  for (int i = 0; i < data.tag_count; ++i)
  {
    auto &msg_tag = msg_data.tags[i];
    auto tag = data.tags[i];
    msg_tag.id = tag->id;
    msg_tag.voltage = tag->voltage;
    msg_tag.anchors.resize(tag->anchor_count);
    for (int j = 0; j < tag->anchor_count; ++j)
    {
      auto &msg_anchor = msg_tag.anchors[j];
      auto anchor = tag->anchors[j];
      msg_anchor.id = anchor->id;
      msg_anchor.dis = anchor->dis;
    }
  }

  publisher_->publish(msg_data); 
}    

