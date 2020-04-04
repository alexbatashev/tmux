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

#include <ntmux/Server.hpp>

#include <Multiplexer.pb.h>

#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/status.h>

#include <array>

// todo replace with a real command execution via terminals
static std::string exec(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}
::grpc::Status Server::executeCommand(::grpc::ServerContext *context,
                                      const ::ntmux::Command *request,
                                      ::ntmux::ExecutionStatus *response) {
  auto res = exec(request->cli().c_str());
  response->set_status("OK");
  response->set_output(res);
  return grpc::Status::OK;
}
