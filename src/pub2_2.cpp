#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>
#include <chrono>
#include <functional>
//#include <string>
using namespace std::chrono_literals;
void callback(rclcpp::Node::SharedPtr node, 
rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr pub)
{
    geometry_msgs::msg::Vector3 number;
    std::cout << "입력하시오\n";
    std::cin >> number.x;
    std::cin >> number.y;
    std::cin >> number.z;
    RCLCPP_INFO(node->get_logger(), "x: %lf\n y: %lf\n z: %lf\n",number.x,number.y,number.z );
    pub->publish(number);
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("mynode");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Vector3>("mytopic", qos_profile
    );
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(100ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}