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

#ifndef CPP_TMUX_WINDOW_HPP
#define CPP_TMUX_WINDOW_HPP

#include <cstddef>
#include <string>

class Window {
private:
  size_t mId = 0; // fixme id must be provided to the constructor
  void *mLatest{}; // fixme provide actual type here

  std::string mName = "";
  void *mNameEvent{}; // fixme actual type here
  void *mNameTime{};  // fixme actual type here

  void *mAlertsTimer{}; // fixme actual type here
  void *mOffsetTimer{}; // fixme actual type here

  void *mActivityTime{}; // fixme actual type here

  void *mActivePane{};
  void *mLastPane{};
  void *mPanes{};

  int mLastLayout = -1;
  void *mLayoutRoot{};      // fixme actual type
  void *mSavedLayoutRoot{}; // fixme actual type
  char *mOldLayout{};       // fixme actual type

  size_t mX;
  size_t mY;
  size_t mXPixel;
  size_t mYPixel;

  int flags = 0; // fixme std::bitset?

  // fixme enum class?
  static constexpr size_t WINDOW_BELL = 0x1;
  static constexpr size_t WINDOW_ACTIVITY = 0x2;
  static constexpr size_t WINDOW_SILENCE = 0x4;
  static constexpr size_t WINDOW_ZOOMED = 0x8;
  static constexpr size_t WINDOW_WASZOOMED = 0x10;
  static constexpr size_t WINDOW_ALERTFLAGS =
      (WINDOW_BELL | WINDOW_ACTIVITY | WINDOW_SILENCE);

  int mAlertsQueued = 0;
  void *mAlertsEntry{}; // fixme actual type

  void *mOptions{}; // fixme actual type

  size_t mReferences{}; // fixme std::shared_ptr?
  void *mWinLinks{};

  void *mEntry{};

public:
  Window(size_t x, size_t y, size_t xPixel, size_t yPixel) :
    mX(x), mY(y), mXPixel(xPixel), mYPixel(yPixel) {}
};

#endif // CPP_TMUX_WINDOW_HPP
