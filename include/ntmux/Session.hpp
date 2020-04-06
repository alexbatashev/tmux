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

#ifndef NEOTMUX_SESSION_HPP
#define NEOTMUX_SESSION_HPP

#include "Interface.pb.h"

namespace ntmux {
class Session final : public SessionData {
public:
  Session(std::string sessionName, bool isNew) {
    set_name(std::move(sessionName));

    if (isNew) {
    }
  }
};
}

#endif // NEOTMUX_SESSION_HPP
