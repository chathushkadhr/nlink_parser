#ifndef NLT_ANCHORFRAME_H
#define NLT_ANCHORFRAME_H

#include "rclcpp/rclcpp.hpp"

#include "nlink_parser/linktrack/utility.h"
#include "nlink_protocol.h"
#include "nlink_unpack/nlink_linktrack_anchorframe0.h"
#include "nlink_parser/msg/linktrack_anchorframe0.hpp"



class NLT_ProtocolAnchorFrame0 : public NLinkProtocol
{
public:
  NLT_ProtocolAnchorFrame0(rclcpp::Node *node);
  
protected:
  void UnpackFrameData(const uint8_t *data) override {};
  void HandleData(const uint8_t *data) override;
  bool Verify(const uint8_t *data);

private:
  rclcpp::Publisher<nlink_parser::msg::LinktrackAnchorframe0>::SharedPtr publisher_;
  rclcpp::Node *node_;
  std::string topic;
  
  rclcpp::Logger logger_;
  rclcpp::Clock clock_;
};

#endif // NLT_ANCHORFRAME_H
