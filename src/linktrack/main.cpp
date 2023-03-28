#include <nlink_parser/linktrack/linktrack_driver.hpp>

using namespace nlink_parser;

int main(int argc, char * argv[])
{
  
  rclcpp::init(argc, argv);
  
  rclcpp::spin(std::make_shared<LinkTrack>());
  rclcpp::shutdown();
  
  return EXIT_SUCCESS;
}