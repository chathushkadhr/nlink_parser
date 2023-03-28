#ifndef NLT_NODEFRAME2_H
#define NLT_NODEFRAME2_H

#include "rclcpp/rclcpp.hpp"

#include "nlink_parser/linktrack/utility.h"
#include "nlink_protocol.h"
#include "nlink_unpack/nlink_linktrack_nodeframe2.h"
#include "nlink_parser/msg/linktrack_nodeframe2.hpp"



class NLT_ProtocolNodeFrame2 : public NLinkProtocolVLength
{
public:
  NLT_ProtocolNodeFrame2(rclcpp::Node *node);

protected:
  void UnpackFrameData(const uint8_t *data) override {};
  void HandleData(const uint8_t *data) override;

private:
  rclcpp::Publisher<nlink_parser::msg::LinktrackNodeframe2>::SharedPtr publisher_;
  rclcpp::Node *node_;
  std::string topic;
  
  rclcpp::Logger logger_;
  rclcpp::Clock clock_;
};

#endif // NLT_NODEFRAME2_H