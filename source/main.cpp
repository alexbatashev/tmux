//===----------------------------------------------------------------------===//
// Copyright (c) 2020 Alexander Batashev. All rights reserved.
//
// Licensed under MIT license.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.
//===----------------------------------------------------------------------===//

#include <ntmux/Window.hpp>

#include "cxxopts.hpp"

#include "Multiplexer.pb.h"

#include <iostream>

/// \file main.cpp
/// For now, it is just a stub cpp file to make target compilable

int main(int argc, char *argv[]) {
  cxxopts::Options opts("NeoTmux", "Terminal multiplexer");
  opts.add_options()
      ("command", "command", cxxopts::value<std::string>())
      ("s", "Session name", cxxopts::value<std::string>());

  opts.parse_positional("command");

  auto result = opts.parse(argc, argv);

  std::cout << result["command"].as<std::string>() << std::endl;
  std::cout << result["s"].as<std::string>() << std::endl;

  return 0;
}
