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

#include "ntmux/Client.hpp"
#include "util/MockServer.hpp"
#include "util/server_helpers.h"

#include "catch2/catch.hpp"

#include <thread>

TEST_CASE("NeoTmux Client") {
  MockServer service;
  auto server = createServer(service);
  auto serverRunner = [&]() { server->Wait(); };
  std::thread serverThread(serverRunner);

  // fixme there must be a better way to wait for server to start
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  auto channel = grpc::CreateChannel(kServerAddress, grpc::InsecureChannelCredentials());

  Client client(channel);
  const auto res = client.executeSampleCommand();

  REQUIRE(res.ok());

  server->Shutdown();
  serverThread.join();
}
