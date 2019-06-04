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

#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "rtmonitor/rtmonitor.hpp"

class RTNode : public rclcpp::Node
{
public:
  RTNode()
  : Node("rt_node")
  {
    rtm_.init("test_rtm", 10 /*rate*/, 5 /*margin %age*/,
      std::bind(&RTNode::cbLooptimeOverrun, this,
      std::placeholders::_1, std::placeholders::_2));
  }
  ~RTNode() {}
  void loop_function()
  {
    rtm_.calc_looptime("test_rtm", this->now());
  }
  void cbLooptimeOverrun(int iter_num, rclcpp::Duration jitter)
  {
    printf("Missed Deadline : %d\n", iter_num);
    (void) jitter;
  }

private:
  rtmonitor::RealTimeMonitor rtm_;
};

volatile sig_atomic_t stop;

void inthand(int signum)
{
  stop = 1;
  (void)signum;
}

int main(int argc, char * argv[])
{
  printf("Test real time monitor \n");

  signal(SIGINT, inthand);

  rclcpp::init(argc, argv);

  RTNode rt_node;
  while (!stop) {
    rt_node.loop_function();
    usleep(110000);
  }

  rclcpp::shutdown();

  return 0;
}
