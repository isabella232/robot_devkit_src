// Copyright (c) 2019 Intel Corporation
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

#include "rtmonitor/rtm_publisher.hpp"

namespace rtmonitor
{

RtmPublisher::RtmPublisher(rclcpp::Node::SharedPtr node)
{
  create_publisher_looptime(node);
  create_publisher_perfmetric(node);
}

RtmPublisher::~RtmPublisher()
{
}

bool RtmPublisher::create_publisher_looptime(rclcpp::Node::SharedPtr node)
{
  pub_looptime_ = node->create_publisher<rtmonitor_msgs::msg::LoopTime>("rtm_looptime", 10);
}

bool RtmPublisher::publish_looptime(rtmonitor_msgs::msg::LoopTime msg)
{
  // rtmonitor_msgs::msg::LoopTime msg;
  // msg.iteration = 0;
  pub_looptime_->publish(msg);

  return true;
}

bool RtmPublisher::create_publisher_perfmetric(rclcpp::Node::SharedPtr node)
{
  pub_perfmetric_ = node->create_publisher<rtmonitor_msgs::msg::PerfMetric>("rtm_perfmetric", 10);
}

bool RtmPublisher::publish_perfmetric(rtmonitor_msgs::msg::PerfMetric msg)
{
  pub_perfmetric_->publish(msg);

  return true;
}

}   // namespace rtmonitor
