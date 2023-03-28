#ifndef NLT_TAGFRAME0_H
#define NLT_TAGFRAME0_H

#include "rclcpp/rclcpp.hpp"

#include "nlink_parser/linktrack/utility.h"
#include "nlink_protocol.h"
#include "nlink_unpack/nlink_linktrack_tagframe0.h"
#include "nlink_parser/msg/linktrack_tagframe0.hpp"



class NLT_ProtocolTagFrame0 : public NLinkProtocol
{
public:
  NLT_ProtocolTagFrame0(rclcpp::Node *node);

protected:
  void UnpackFrameData(const uint8_t *data) override {};
  void HandleData(const uint8_t *data) override;

private:
  rclcpp::Publisher<nlink_parser::msg::LinktrackTagframe0>::SharedPtr publisher_;
  rclcpp::Node *node_;
  std::string topic;
  
  rclcpp::Logger logger_;
  rclcpp::Clock clock_;
};

#endif // NLT_TAGFRAME0_H
