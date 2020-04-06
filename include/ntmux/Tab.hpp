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

#ifndef NEOTMUX_TAB_HPP
#define NEOTMUX_TAB_HPP

#include "Interface.pb.h"
namespace ntmux {
class Tab final : public TabData {
public:
  Tab() {
    set_name("");
    set_id(0);
  }

  void renderTab() {

  }
};
}

#endif // NEOTMUX_TAB_HPP
