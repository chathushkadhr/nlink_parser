#include "nlink_parser/linktrack/protocols/nlt_tagframe0.h"

NLT_ProtocolTagFrame0::NLT_ProtocolTagFrame0(rclcpp::Node *node)
    : NLinkProtocol(
          true, g_nlt_tagframe0.fixed_part_size,
          {g_nlt_tagframe0.frame_header, g_nlt_tagframe0.function_mark}
          ),
      publisher_(nullptr),
      node_(node),
      topic("nlink_linktrack_tagframe0"),
      logger_(rclcpp::get_logger("NLT_ProtocolTagFrame0")),
      clock_(rclcpp::Clock())
{
  if (node_!=nullptr)
    logger_ = node_->get_logger();
}

void NLT_ProtocolTagFrame0::HandleData(const uint8_t *serial_data)
{
  
  if (node_==nullptr){
    RCLCPP_ERROR_THROTTLE(logger_, clock_, 1.0 , "Node is a null pointer");
    return;
  }

  nlink_parser::msg::LinktrackTagframe0 g_msg_tagframe0;
  g_nlt_tagframe0.UnpackData(serial_data, length());

  if (publisher_==nullptr){
    publisher_ = node_->create_publisher<nlink_parser::msg::LinktrackTagframe0>(topic, 200);
    RCLCPP_INFO_STREAM( node_->get_logger() , 
    std::string(topic) << " has been advertised,use 'ros2 topic echo " << 
    std::string(topic) << "' to view the data");
  }

  const auto &data = g_nlt_tagframe0.result;
  auto &msg_data = g_msg_tagframe0;

  msg_data.role = data.role;
  msg_data.id = data.id;
  msg_data.local_time = data.local_time;
  msg_data.system_time = data.system_time;
  msg_data.voltage = data.voltage;
  ARRAY_ASSIGN(msg_data.pos_3d, data.pos_3d)
  ARRAY_ASSIGN(msg_data.eop_3d, data.eop_3d)
  ARRAY_ASSIGN(msg_data.vel_3d, data.vel_3d)
  ARRAY_ASSIGN(msg_data.dis_arr, data.dis_arr)
  ARRAY_ASSIGN(msg_data.imu_gyro_3d, data.imu_gyro_3d)
  ARRAY_ASSIGN(msg_data.imu_acc_3d, data.imu_acc_3d)
  ARRAY_ASSIGN(msg_data.angle_3d, data.angle_3d)
  ARRAY_ASSIGN(msg_data.quaternion, data.quaternion)
  
  publisher_->publish(msg_data); 
}    

