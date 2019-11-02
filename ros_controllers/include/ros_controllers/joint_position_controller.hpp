// Copyright 2019 SIW Manufacturing Sdn. Bhd.
// Poh Zhi-Ee <zhiee.poh@httechnology.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROS_CONTROLLERS__JOINT_POSITION_CONTROLLER_HPP_
#define ROS_CONTROLLERS__JOINT_POSITION_CONTROLLER_HPP_

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "controller_interface/controller_interface.hpp"

#include "hardware_interface/robot_hardware.hpp"

#include "rclcpp_lifecycle/state.hpp"

#include "ros_controllers/visibility_control.h"

#include "sensor_msgs/msg/joint_state.hpp"

#include "ros2_control_interfaces/msg/joint_control.hpp"

#include "parameter_server_interfaces/srv/get_controller_pid.hpp"
#include "parameter_server_interfaces/srv/get_controller_joints.hpp"

#include "ros2_control_helpers/pid.hpp"

namespace ros_controllers
{

class JointPositionController : public controller_interface::ControllerInterface
{
public:
    ROS_CONTROLLERS_PUBLIC
    JointPositionController();

    ROS_CONTROLLERS_PUBLIC
    controller_interface::controller_interface_ret_t
    init( std::weak_ptr<hardware_interface::RobotHardware> robot_hardware,
          const std::string &controller_name ) override;

    ROS_CONTROLLERS_PUBLIC
    controller_interface::controller_interface_ret_t
    update() override;

    ROS_CONTROLLERS_PUBLIC
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_configure(const rclcpp_lifecycle::State &previous_state) override;

    ROS_CONTROLLERS_PUBLIC
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_activate(const rclcpp_lifecycle::State &previous_state) override;

    ROS_CONTROLLERS_PUBLIC
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_deactivate(const rclcpp_lifecycle::State &previous_state) override;

    ROS_CONTROLLERS_PUBLIC
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_cleanup(const rclcpp_lifecycle::State &previous_state) override;

    ROS_CONTROLLERS_PUBLIC
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_error(const rclcpp_lifecycle::State &previous_state) override;

    ROS_CONTROLLERS_PUBLIC
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_shutdown(const rclcpp_lifecycle::State &previous_state) override;

private:

    // joint handles
    std::vector<hardware_interface::JointCommandHandle*> registered_joint_cmd_handles_ = {};
    std::vector<const hardware_interface::JointStateHandle*> registered_joint_state_handles_ = {};
    
    std::vector<std::shared_ptr<control_helpers::Pid>> pid_controllers_ = {};
    // std::vector<double> desired_pos_vec_;

    std::unordered_map<std::string, double> desired_pos_map_ = {};
    std::unordered_map<std::string, std::shared_ptr<control_helpers::Pid>> pid_controllers_map_ = {};


    rclcpp::Subscription<ros2_control_interfaces::msg::JointControl>::SharedPtr subscription_;

    rclcpp::Time previous_update_time_;

    // get-functions
    control_helpers::Pid::Gains get_controller_pid();
    std::vector<std::string> get_controller_joints();

    // callback
    void desired_position_subscrition_callback(ros2_control_interfaces::msg::JointControl::UniquePtr msg);
};

} // namespace ros_controllers

#endif // ROS_CONTROLLERS__JOINT_POSITION_CONTROLLER_HPP_