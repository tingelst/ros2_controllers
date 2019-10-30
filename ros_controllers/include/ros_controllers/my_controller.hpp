#ifndef ROS_CONTROLLERS__JOINT_STATE_CONTROLLER_HPP_
#define ROS_CONTROLLERS__JOINT_STATE_CONTROLLER_HPP_

#include <memory>
#include <string>
#include <vector>

#include "controller_interface/controller_interface.hpp"

#include "hardware_interface/robot_hardware.hpp"

#include "rclcpp_lifecycle/state.hpp"

#include "ros_controllers/visibility_control.h"

#include "sensor_msgs/msg/joint_state.hpp"

namespace ros_controllers
{


//my_controller = rewrite of joint state controller
class my_controller : public controller_interface::ControllerInterface
{
public:
  ROS_CONTROLLERS_PUBLIC
  my_controller();

  ROS_CONTROLLERS_PUBLIC
  controller_interface::controller_interface_ret_t
  update() override;

  ROS_CONTROLLERS_PUBLIC
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State & previous_state) override;

private:
  std::vector<const hardware_interface::JointStateHandle*> registered_joint_handles_;

  std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<sensor_msgs::msg::JointState>> joint_state_publisher_;
  
  sensor_msgs::msg::JointState joint_state_msg_;
};

}  // namespace ros_controllers

#endif  // ROS_CONTROLLERS__JOINT_STATE_CONTROLLER_HPP_
