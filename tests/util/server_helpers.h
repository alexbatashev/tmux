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

#ifndef CPP_TMUX_SERVER_HELPERS_H
#define CPP_TMUX_SERVER_HELPERS_H

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

static const std::string kServerAddress = "0.0.0.0:50051";

template <typename ServerT>
std::unique_ptr<grpc::Server> createServer(ServerT&service) {
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder builder;
  builder.AddListeningPort(kServerAddress, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  return server;
}
#endif // CPP_TMUX_SERVER_HELPERS_H
