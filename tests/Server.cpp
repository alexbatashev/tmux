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

#include "ntmux/Server.hpp"
#include "util/server_helpers.h"

#include "catch2/catch.hpp"

#include <thread>

TEST_CASE("NeoTmux Server") {
  Server service;
  auto server = createServer(service);
  auto serverRunner = [&]() { server->Wait(); };
  std::thread serverThread(serverRunner);

  // fixme there must be a better way to wait for server to start
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  auto channel = grpc::CreateChannel(kServerAddress, grpc::InsecureChannelCredentials());

  auto stub = ntmux::Multiplexer::NewStub(channel);

  grpc::ClientContext ctx;
  ntmux::Command cmd;
  cmd.set_cli("echo 1");

  ntmux::ExecutionStatus executionStatus;

  auto res = stub->executeCommand(&ctx, cmd, &executionStatus);

  REQUIRE(res.ok());
  REQUIRE(executionStatus.output() == "1\n");

  server->Shutdown();
  serverThread.join();
}
