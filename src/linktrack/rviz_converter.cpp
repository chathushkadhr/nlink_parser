#include "nlink_parser/linktrack/rviz_converter.hpp"

using namespace rviz_converter;
using std::placeholders::_1;

RVizConverter:: RVizConverter() : 
    Node("rviz_converter"),
    publisher_anchorframe0_ (nullptr),
    publisher_nodeframe1_(nullptr),
    publisher_tagframe0_(nullptr),
    publisher_nodeframe2_(nullptr)
 
{   this->declare_parameter("~map_frame", "linktrack_map");
    frameId = this->get_parameter("~map_frame").get_parameter_value().get<std::string>();

    sub_anchorframe0_ = this->create_subscription<nlink_parser::msg::LinktrackAnchorframe0>(
      "nlink_linktrack_anchorframe0", 10, std::bind(&RVizConverter::Anchorframe0Callback, this, _1));
  

    sub_tagframe0_ = this->create_subscription<nlink_parser::msg::LinktrackTagframe0>(
      "nlink_linktrack_tagframe0", 10, std::bind(&RVizConverter::Tagframe0Callback, this, _1));
    
    sub_nodeframe1_ = this->create_subscription<nlink_parser::msg::LinktrackNodeframe1>(
      "nlink_linktrack_nodeframe1", 10, std::bind(&RVizConverter::Nodeframe1Callback, this, _1));
 
    sub_nodeframe2_ = this->create_subscription<nlink_parser::msg::LinktrackNodeframe2>(
      "nlink_linktrack_nodeframe2", 10, std::bind(&RVizConverter::Nodeframe2Callback, this, _1));
   
}


void RVizConverter::Anchorframe0Callback(const nlink_parser::msg::LinktrackAnchorframe0 & msg)
{

  for (const auto &node : msg.nodes)
  {
    auto id = node.id;

    if (publisher_anchorframe0_==nullptr)
    {
      std::ostringstream string_stream;
      string_stream << "nlt_anchorframe0_pose_node" << static_cast<int>(id);
      auto topic = string_stream.str();
      publisher_anchorframe0_ = this->create_publisher<geometry_msgs::msg::PoseStamped>(topic, 10);
      RCLCPP_INFO(this->get_logger(), topic.c_str());
      msg_pose_anchorframe0_.header.frame_id = frameId;
      msg_pose_anchorframe0_.pose.orientation.w = 0;
      msg_pose_anchorframe0_.pose.orientation.x = 0;
      msg_pose_anchorframe0_.pose.orientation.y = 0;
      msg_pose_anchorframe0_.pose.orientation.z = 1;
    }
    //++msg_pose.header.seq;
    msg_pose_anchorframe0_.header.stamp = rclcpp::Time(); // ros::Time(msg.system_time / 1000.0)
    msg_pose_anchorframe0_.pose.position.x = static_cast<double>(node.pos_3d[0]);
    msg_pose_anchorframe0_.pose.position.y = static_cast<double>(node.pos_3d[1]);
    msg_pose_anchorframe0_.pose.position.z = static_cast<double>(node.pos_3d[2]);
    publisher_anchorframe0_->publish(msg_pose_anchorframe0_);
  }
}

void RVizConverter::Nodeframe1Callback(const nlink_parser::msg::LinktrackNodeframe1 &msg)
{
  for (const auto &node : msg.nodes)
  {
    auto id = node.id;

    if (publisher_nodeframe1_==nullptr)
    {
      std::ostringstream string_stream;
      string_stream << "nlt_nodeframe1_pose_node" << static_cast<int>(id);
      auto topic = string_stream.str();
      publisher_nodeframe1_ = this->create_publisher<geometry_msgs::msg::PoseStamped>(topic, 10);
      //     ros::NodeHandle().advertise<geometry_msgs::msg::PoseStamped>(topic, 10);
      // TopicAdvertisedTip(topic.c_str());
   
      msg_pose_nodeframe1_.header.frame_id = frameId;
      msg_pose_nodeframe1_.pose.orientation.w = 0;
      msg_pose_nodeframe1_.pose.orientation.x = 0;
      msg_pose_nodeframe1_.pose.orientation.y = 0;
      msg_pose_nodeframe1_.pose.orientation.z = 1;
    }

    //++msg_pose.header.seq;
    msg_pose_nodeframe1_.header.stamp = rclcpp::Time(); // ros::Time(msg.system_time / 1000.0)
    msg_pose_nodeframe1_.pose.position.x = static_cast<double>(node.pos_3d[0]);
    msg_pose_nodeframe1_.pose.position.y = static_cast<double>(node.pos_3d[1]);
    msg_pose_nodeframe1_.pose.position.z = static_cast<double>(node.pos_3d[2]);
    publisher_nodeframe1_->publish(msg_pose_nodeframe1_);
  }
}

void RVizConverter::Tagframe0Callback(const nlink_parser::msg::LinktrackTagframe0 &msg)
{

  if (publisher_tagframe0_==nullptr)
  {
    
    auto topic = "nlt_tagframe0_pose";
    publisher_tagframe0_ = this->create_publisher<geometry_msgs::msg::PoseStamped>(topic, 10);
    //     ros::NodeHandle().advertise<geometry_msgs::PoseStamped>(topic, 10);
    // TopicAdvertisedTip(topic);
    msg_pose_tagframe0_.header.frame_id = frameId;
  }
 
  //++msg_pose.header.seq;
  msg_pose_tagframe0_.header.stamp = rclcpp::Time(); // ros::Time(msg.system_time / 1000.0)
  msg_pose_tagframe0_.pose.orientation.w = static_cast<double>(msg.quaternion[0]);
  msg_pose_tagframe0_.pose.orientation.x = static_cast<double>(msg.quaternion[1]);
  msg_pose_tagframe0_.pose.orientation.y = static_cast<double>(msg.quaternion[2]);
  msg_pose_tagframe0_.pose.orientation.z = static_cast<double>(msg.quaternion[3]);
  msg_pose_tagframe0_.pose.position.x = static_cast<double>(msg.pos_3d[0]);
  msg_pose_tagframe0_.pose.position.y = static_cast<double>(msg.pos_3d[1]);
  msg_pose_tagframe0_.pose.position.z = static_cast<double>(msg.pos_3d[2]);
  publisher_tagframe0_->publish(msg_pose_tagframe0_);
}

void RVizConverter::Nodeframe2Callback(const nlink_parser::msg::LinktrackNodeframe2 &msg)
{

  if (publisher_nodeframe2_==nullptr)
  {
    auto topic = "nlt_nodeframe2_pose";
    publisher_nodeframe2_ = this->create_publisher<geometry_msgs::msg::PoseStamped>(topic, 10);
    //     ros::NodeHandle().advertise<geometry_msgs::PoseStamped>(topic, 10);
    // TopicAdvertisedTip(topic);
    msg_pose_nodeframe2_.header.frame_id = frameId;
  }
  //++msg_pose.header.seq;
  msg_pose_nodeframe2_.header.stamp = rclcpp::Time(); // ros::Time(msg.system_time / 1000.0)
  msg_pose_nodeframe2_.pose.orientation.w = static_cast<double>(msg.quaternion[0]);
  msg_pose_nodeframe2_.pose.orientation.x = static_cast<double>(msg.quaternion[1]);
  msg_pose_nodeframe2_.pose.orientation.y = static_cast<double>(msg.quaternion[2]);
  msg_pose_nodeframe2_.pose.orientation.z = static_cast<double>(msg.quaternion[3]);
  msg_pose_nodeframe2_.pose.position.x = static_cast<double>(msg.pos_3d[0]);
  msg_pose_nodeframe2_.pose.position.y = static_cast<double>(msg.pos_3d[1]);
  msg_pose_nodeframe2_.pose.position.z = static_cast<double>(msg.pos_3d[2]);
  publisher_nodeframe2_->publish(msg_pose_nodeframe2_);
}
