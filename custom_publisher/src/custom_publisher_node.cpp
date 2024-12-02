#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/custom.hpp" // 수정된 헤더 파일

class CustomPublisher : public rclcpp::Node
{
public:
    CustomPublisher() : Node("custom_publisher")
    {
        publisher_ = this->create_publisher<custom_interfaces::msg::Custom>("custom_topic", 10);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&CustomPublisher::publish_message, this));
    }

private:
    void publish_message()
    {
        auto message = custom_interfaces::msg::Custom();
        message.start = true; 
        message.count = num++;   

        RCLCPP_INFO(this->get_logger(), "Publishing: start=%d, count=%d", message.start, message.count);
        publisher_->publish(message);
    }

    rclcpp::Publisher<custom_interfaces::msg::Custom>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int num=0;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CustomPublisher>());
    rclcpp::shutdown();
    return 0;
}
