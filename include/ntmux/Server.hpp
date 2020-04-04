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

#ifndef CPP_TMUX_SERVER_HPP
#define CPP_TMUX_SERVER_HPP

#include "Multiplexer.grpc.pb.h"

class Server final : public ntmux::Multiplexer::Service {
public:
  grpc::Status executeCommand(::grpc::ServerContext *context,
                              const ::ntmux::Command *request,
                              ::ntmux::ExecutionStatus *response) override;
};

#endif // CPP_TMUX_SERVER_HPP
