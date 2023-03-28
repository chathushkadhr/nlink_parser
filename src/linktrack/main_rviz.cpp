#include <nlink_parser/linktrack/rviz_converter.hpp>

using namespace rviz_converter;

int main(int argc, char * argv[])
{
  
  rclcpp::init(argc, argv);
  
  rclcpp::spin(std::make_shared<RVizConverter>());
  rclcpp::shutdown();
  
  return EXIT_SUCCESS;
}