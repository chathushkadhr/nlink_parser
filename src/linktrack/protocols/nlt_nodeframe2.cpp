#include "nlink_parser/linktrack/protocols/nlt_nodeframe2.h"

NLT_ProtocolNodeFrame2::NLT_ProtocolNodeFrame2(rclcpp::Node *node)
    : NLinkProtocolVLength(
          true, g_nlt_nodeframe2.fixed_part_size,
          {g_nlt_nodeframe2.frame_header, g_nlt_nodeframe2.function_mark}
          ),
      publisher_(nullptr),
      node_(node),
      topic("nlink_linktrack_nodeframe2"),
      logger_(rclcpp::get_logger("NLT_ProtocolNodeFrame2")),
      clock_(rclcpp::Clock())
{
  if (node_!=nullptr)
    logger_ = node_->get_logger();
}

void NLT_ProtocolNodeFrame2::HandleData(const uint8_t *serial_data)
{
  
  if (node_==nullptr){
    RCLCPP_ERROR_THROTTLE(logger_, clock_, 1.0 , "Node is a null pointer");
    return;
  }

  nlink_parser::msg::LinktrackNodeframe2 g_msg_nodeframe2;
  g_nlt_nodeframe2.UnpackData(serial_data, length());

  if (publisher_==nullptr){
    publisher_ = node_->create_publisher<nlink_parser::msg::LinktrackNodeframe2>(topic, 200);
    RCLCPP_INFO_STREAM( node_->get_logger() , 
    std::string(topic) << " has been advertised,use 'ros2 topic echo " << 
    std::string(topic) << "' to view the data");
  }

  const auto &data = g_nlt_nodeframe2.result;
  auto &msg_data = g_msg_nodeframe2;
  auto &msg_nodes = msg_data.nodes;

  msg_data.role = data.role;
  msg_data.id = data.id;
  msg_data.local_time = data.local_time;
  msg_data.system_time = data.system_time;
  msg_data.voltage = data.voltage;
  ARRAY_ASSIGN(msg_data.pos_3d, data.pos_3d)
  ARRAY_ASSIGN(msg_data.eop_3d, data.eop_3d)
  ARRAY_ASSIGN(msg_data.vel_3d, data.vel_3d)
  ARRAY_ASSIGN(msg_data.imu_gyro_3d, data.imu_gyro_3d)
  ARRAY_ASSIGN(msg_data.imu_acc_3d, data.imu_acc_3d)
  ARRAY_ASSIGN(msg_data.angle_3d, data.angle_3d)
  ARRAY_ASSIGN(msg_data.quaternion, data.quaternion)

  msg_nodes.resize(data.valid_node_count);
  for (size_t i = 0; i < data.valid_node_count; ++i)
  {
    auto &msg_node = msg_nodes[i];
    auto node = data.nodes[i];
    msg_node.id = node->id;
    msg_node.role = node->role;
    msg_node.dis = node->dis;
    msg_node.fp_rssi = node->fp_rssi;
    msg_node.rx_rssi = node->rx_rssi;
  } 

  publisher_->publish(msg_data); 
}    

