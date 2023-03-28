#include <chrono>
#include <memory>
#include <string>
#include <functional>

#include "geometry_msgs/msg/pose_array.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/path.hpp"
#include "nlink_parser/msg/linktrack_anchorframe0.hpp"
#include "nlink_parser/msg/linktrack_nodeframe1.hpp"
#include "nlink_parser/msg/linktrack_nodeframe2.hpp"
#include "nlink_parser/msg/linktrack_tagframe0.hpp"

#include "rclcpp/rclcpp.hpp"


#include <map>
#include <sstream>


using std::placeholders::_1;

namespace rviz_converter{
  
  class RVizConverter : public rclcpp::Node
  {
    public:
      RVizConverter();

    private:
      std::string frameId;

      void Anchorframe0Callback(const nlink_parser::msg::LinktrackAnchorframe0 &msg);
      void Tagframe0Callback(const nlink_parser::msg::LinktrackTagframe0 &msg);
      void Nodeframe1Callback(const nlink_parser::msg::LinktrackNodeframe1 &msg);
      void Nodeframe2Callback(const nlink_parser::msg::LinktrackNodeframe2 &msg);

      rclcpp::Subscription<nlink_parser::msg::LinktrackAnchorframe0>::SharedPtr sub_anchorframe0_;
      rclcpp::Subscription<nlink_parser::msg::LinktrackTagframe0>::SharedPtr sub_tagframe0_;
      rclcpp::Subscription<nlink_parser::msg::LinktrackNodeframe1>::SharedPtr sub_nodeframe1_;
      rclcpp::Subscription<nlink_parser::msg::LinktrackNodeframe2>::SharedPtr sub_nodeframe2_;

      rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_anchorframe0_;
      rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_nodeframe1_;
      rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_tagframe0_;
      rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_nodeframe2_;

      geometry_msgs::msg::PoseStamped msg_pose_anchorframe0_;
      geometry_msgs::msg::PoseStamped msg_pose_nodeframe1_;
      geometry_msgs::msg::PoseStamped msg_pose_tagframe0_;
      geometry_msgs::msg::PoseStamped msg_pose_nodeframe2_;
  };
}
