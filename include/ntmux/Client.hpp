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

#ifndef CPP_TMUX_CLIENT_HPP
#define CPP_TMUX_CLIENT_HPP

#include "Multiplexer.grpc.pb.h"

class Client {
private:
  grpc::ClientContext mClientContext;
  std::unique_ptr<ntmux::Multiplexer::Stub> mStub;

public:
  Client(const std::shared_ptr<grpc::ChannelInterface> &channel)
      : mStub(ntmux::Multiplexer::NewStub(channel)) {}
  /// This method is for testing only. Will be removed.
  grpc::Status executeSampleCommand() {
    ntmux::Command cmd;
    cmd.set_cli("Test command");

    ntmux::ExecutionStatus executionStatus;

    return mStub->executeCommand(&mClientContext, cmd, &executionStatus);
  }
};

#endif // CPP_TMUX_CLIENT_HPP
