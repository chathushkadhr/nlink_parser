#include "nlink_parser/linktrack/linktrack_driver.hpp"

using namespace nlink_parser;

LinkTrack:: LinkTrack() : 
    Node("linktrack_parser")
 
{ 
    
  initSerial(serial_);
  initDataTransmission();
  initAnchorFrame0(&protocol_extraction);
  initTagFrame0(&protocol_extraction);
  initNodeFrame0(&protocol_extraction);
  initNodeFrame1(&protocol_extraction);
  initNodeFrame2(&protocol_extraction);
  initNodeFrame3(&protocol_extraction);
  initNodeFrame4(&protocol_extraction);
  initNodeFrame5(&protocol_extraction);
  initNodeFrame6(&protocol_extraction);

   timer_ = this->create_wall_timer(std::chrono::milliseconds(20), std::bind(&LinkTrack::timer_callback, this));
    #ifdef DEBUG
    debug_param();
    #endif
}

void LinkTrack::timer_callback()
{
   auto available_bytes = serial_.available();
   std::string str_received;
    if (available_bytes)
    {
      serial_.read(str_received, available_bytes);
      //printHexData(str_received );
      protocol_extraction.AddNewData(str_received);
    }


}


void LinkTrack::initSerial(serial::Serial &serial)
{
  try
  {

    this->declare_parameter("~port_name", "/dev/ttyUSB0");
    std::string port_name = this->get_parameter("~port_name").get_parameter_value().get<std::string>();
    this->declare_parameter("~baud_rate", 921600);
    int baud_rate = this->get_parameter("~baud_rate").get_parameter_value().get<int>();

    serial.setPort(port_name);
    serial.setBaudrate(static_cast<uint32_t>(baud_rate));
    RCLCPP_INFO(this->get_logger(),"try to open serial port with %s,%d", port_name.data(), baud_rate);
    auto timeout = serial::Timeout::simpleTimeout(10);
    // without setTimeout,serial can not write any datae
    // https://stackoverflow.com/questions/52048670/can-read-but-cannot-write-serial-ports-on-ubuntu-16-04/52051660?noredirect=1#comment91056825_52051660
    serial.setTimeout(timeout);
    serial.open();

    if (serial.isOpen())
    {
      RCLCPP_INFO(this->get_logger(),"Serial port opened successfully, waiting for data.");
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(),"Failed to open serial port, please check and retry.");
      exit(EXIT_FAILURE);
    }
  }
  catch (const std::exception &e)
  {
    RCLCPP_ERROR(this->get_logger(),"Unhandled Exception: %s", e.what());
    exit(EXIT_FAILURE);
  }
}

void LinkTrack::printHexData(const std::string &data)
{
  if (!data.empty())
  {
    std::cout << "data received: ";
    for (int i = 0; i < data.size(); ++i)
    {
      std::cout << std::hex << std::setfill('0') << std::setw(2)
                << int(uint8_t(data.at(i))) << " ";
    }
    std::cout << std::endl;
  }
}

 
void LinkTrack::initDataTransmission()
  {
    dt_sub_ = this->create_subscription<std_msgs::msg::String>("nlink_linktrack_data_transmission", 1000, std::bind(&LinkTrack::DTCallback, this, _1));  
  }
    
void LinkTrack::DTCallback(const std_msgs::msg::String::ConstPtr &msg)
{
  if (&serial_)
    serial_.write(msg->data);
}

void LinkTrack::initAnchorFrame0(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolAnchorFrame0(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initTagFrame0(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolTagFrame0(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initNodeFrame0(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolNodeFrame0(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initNodeFrame1(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolNodeFrame1(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initNodeFrame2(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolNodeFrame2(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initNodeFrame3(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolNodeFrame3(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initNodeFrame4(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolNodeFrame4(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initNodeFrame5(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolNodeFrame5(this);
  protocol_extraction->AddProtocol(protocol);
  
} 

void LinkTrack::initNodeFrame6(NProtocolExtracter *protocol_extraction)
{
  
  auto protocol = new NLT_ProtocolNodeFrame6(this);
  protocol_extraction->AddProtocol(protocol);
  
} 