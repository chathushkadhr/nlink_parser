#include <chrono>
#include <memory>
#include <string>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <iomanip>
#include <iostream>

#include "serial/serial.h"

#include "protocol_extracter/nprotocol_extracter.h"

#include "nlink_parser/linktrack/protocols/nlt_anchorframe0.h"
#include "nlink_parser/linktrack/protocols/nlt_tagframe0.h"
#include "nlink_parser/linktrack/protocols/nlt_nodeframe0.h"
#include "nlink_parser/linktrack/protocols/nlt_nodeframe1.h"
#include "nlink_parser/linktrack/protocols/nlt_nodeframe2.h"
#include "nlink_parser/linktrack/protocols/nlt_nodeframe3.h"
#include "nlink_parser/linktrack/protocols/nlt_nodeframe4.h"
#include "nlink_parser/linktrack/protocols/nlt_nodeframe5.h"
#include "nlink_parser/linktrack/protocols/nlt_nodeframe6.h"


using std::placeholders::_1;

namespace nlink_parser{

  class LinkTrack : public rclcpp::Node
  {
    public:
      LinkTrack();

    private:
      serial::Serial serial_;
      
      void timer_callback();
      void initSerial(serial::Serial &serial);
      void printHexData(const std::string &data);
      void DTCallback(const std_msgs::msg::String::ConstPtr &msg);
      
      void initDataTransmission();
      void initAnchorFrame0(NProtocolExtracter *protocol_extraction);
      void initTagFrame0(NProtocolExtracter *protocol_extraction);
      void initNodeFrame0(NProtocolExtracter *protocol_extraction);
      void initNodeFrame1(NProtocolExtracter *protocol_extraction);
      void initNodeFrame2(NProtocolExtracter *protocol_extraction);
      void initNodeFrame3(NProtocolExtracter *protocol_extraction);
      void initNodeFrame4(NProtocolExtracter *protocol_extraction);
      void initNodeFrame5(NProtocolExtracter *protocol_extraction);
      void initNodeFrame6(NProtocolExtracter *protocol_extraction);


      NProtocolExtracter protocol_extraction;
      rclcpp::TimerBase::SharedPtr timer_;
      rclcpp::Subscription<std_msgs::msg::String>::SharedPtr dt_sub_;
      
  };
}
