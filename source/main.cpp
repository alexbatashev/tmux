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

#include <imgui/imgui.h>
#include <imtui/imtui-impl-ncurses.h>
#include <imtui/imtui-impl-text.h>
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

  //std::cout << result["command"].as<std::string>() << std::endl;
  //std::cout << result["s"].as<std::string>() << std::endl;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  auto screen = ImTui_ImplNcurses_Init(true);
  ImTui_ImplText_Init();

  bool demo = true;
  int nframes = 0;
  float fval = 1.23f;

  while (true) {
    ImTui_ImplNcurses_NewFrame();
    ImTui_ImplText_NewFrame();

    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(4, 2), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(50.0, 10.0), ImGuiCond_Once);
    ImGui::Begin("Hello, world!");
    ImGui::Text("NFrames = %d", nframes++);
    ImGui::Text("Mouse Pos : x = %g, y = %g", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    ImGui::Text("Time per frame %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Float:");
    ImGui::SameLine();
    ImGui::SliderFloat("##float", &fval, 0.0f, 10.0f);
    ImGui::End();

    bool show_app_style_editor = true;
    ImGui::Begin("Style Editor", &show_app_style_editor);
    ImGui::End();

    ImGui::Render();

    ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), screen);
    ImTui_ImplNcurses_DrawScreen();
  }

  ImTui_ImplText_Shutdown();
  ImTui_ImplNcurses_Shutdown();

  return 0;
}
