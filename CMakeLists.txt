cmake_minimum_required(VERSION 3.2)
project(cpp_tmux C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(LibEvent REQUIRED)
find_package(Curses REQUIRED)
find_package(BISON REQUIRED)

bison_target(TmuxParser ${CMAKE_CURRENT_SOURCE_DIR}/source/cmd-parse.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)

file(GLOB COMPAT source/compat/*.c)

add_executable(tmux
    # todo this mostly looks like an implementation of C++ STL
    ${COMPAT}
	source/alerts.c
	source/arguments.c
	source/attributes.c
	source/cfg.c
	source/client.c
	source/cmd-attach-session.c
	source/cmd-bind-key.c
	source/cmd-break-pane.c
	source/cmd-capture-pane.c
	source/cmd-choose-tree.c
	source/cmd-command-prompt.c
	source/cmd-confirm-before.c
	source/cmd-copy-mode.c
	source/cmd-detach-client.c
	source/cmd-display-menu.c
	source/cmd-display-message.c
	source/cmd-display-panes.c
	source/cmd-find-window.c
	source/cmd-find.c
	source/cmd-if-shell.c
	source/cmd-join-pane.c
	source/cmd-kill-pane.c
	source/cmd-kill-server.c
	source/cmd-kill-session.c
	source/cmd-kill-window.c
	source/cmd-list-buffers.c
	source/cmd-list-clients.c
	source/cmd-list-keys.c
	source/cmd-list-panes.c
	source/cmd-list-sessions.c
	source/cmd-list-windows.c
	source/cmd-load-buffer.c
	source/cmd-lock-server.c
	source/cmd-move-window.c
	source/cmd-new-session.c
	source/cmd-new-window.c
	source/cmd-paste-buffer.c
	source/cmd-pipe-pane.c
	source/cmd-queue.c
	source/cmd-refresh-client.c
	source/cmd-rename-session.c
	source/cmd-rename-window.c
	source/cmd-resize-pane.c
	source/cmd-resize-window.c
	source/cmd-respawn-pane.c
	source/cmd-respawn-window.c
	source/cmd-rotate-window.c
	source/cmd-run-shell.c
	source/cmd-save-buffer.c
	source/cmd-select-layout.c
	source/cmd-select-pane.c
	source/cmd-select-window.c
	source/cmd-send-keys.c
	source/cmd-set-buffer.c
	source/cmd-set-environment.c
	source/cmd-set-option.c
	source/cmd-show-environment.c
	source/cmd-show-messages.c
	source/cmd-show-options.c
	source/cmd-source-file.c
	source/cmd-split-window.c
	source/cmd-swap-pane.c
	source/cmd-swap-window.c
	source/cmd-switch-client.c
	source/cmd-unbind-key.c
	source/cmd-wait-for.c
	source/cmd.c
	source/colour.c
	source/control-notify.c
	source/control.c
	source/environ.c
	source/file.c
	source/format.c
	source/format-draw.c
	source/grid-view.c
	source/grid.c
	source/input-keys.c
	source/input.c
	source/job.c
	source/key-bindings.c
	source/key-string.c
	source/layout-custom.c
	source/layout-set.c
	source/layout.c
	source/log.c
	source/menu.c
	source/mode-tree.c
	source/names.c
	source/notify.c
	source/options-table.c
	source/options.c
	source/paste.c
	source/popup.c
	source/proc.c
	source/regsub.c
	source/resize.c
	source/screen-redraw.c
	source/screen-write.c
	source/screen.c
	source/server-client.c
	source/server-fn.c
		source/server_helpers.c
	source/session.c
	source/spawn.c
	source/status.c
	source/style.c
	source/tmux.c
	source/tty-acs.c
	source/tty-keys.c
	source/tty-term.c
	source/tty.c
	source/utf8.c
	source/window-buffer.c
	source/window-client.c
	source/window-clock.c
	source/window-copy.c
	source/window-tree.c
	source/window.c
	source/xmalloc.c
	source/xterm-keys.c
    source/osdep-linux.c # todo support other platforms
    ${BISON_TmuxParser_OUTPUTS} # todo look for a way to remove bison
)

target_include_directories(tmux PRIVATE 
                            include
                            ${LIBEVENT_INCLUDE_DIR}
                            ${CURSES_INCLUDE_DIRS})
target_link_libraries(tmux PRIVATE ${LIBEVENT_LIB} ${CURSES_LIBRARIES} m util)
target_compile_definitions(tmux PRIVATE TMUX_VERSION="0.1")

if(CURSES_HAVE_CURSES_H)
  target_compile_definitions(tmux PRIVATE HAVE_CURSES_H)
elseif(CURSES_HAVE_NCURSES_H)
  target_compile_definitions(tmux PRIVATE HAVE_NCURSES_H)
endif()

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(PROTOS
		${CMAKE_CURRENT_SOURCE_DIR}/proto/Multiplexer.proto
		)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})


set(NTMUX_SRC
		source/Window.cpp
		source/Client.cpp
		source/Server.cpp
		${PROTO_SRCS}
		${GRPC_SRCS} source/Server.cpp)

add_library(ntmux_core STATIC ${NTMUX_SRC})
add_executable(ntmux source/main.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${PROTO_SRC_DIR}) # todo figure out if there's a way to get rid of this

add_subdirectory(contrib/Catch2)
add_subdirectory(contrib/cxxopts)
add_subdirectory(contrib/imtui)

target_link_libraries(ntmux_core PUBLIC
		imtui-ncurses
		gRPC::grpc++_reflection
		protobuf::libprotobuf)
target_include_directories(ntmux_core PUBLIC include ${PROTO_SRC_DIR})

target_link_libraries(ntmux PRIVATE
						ntmux_core
						cxxopts::cxxopts)

enable_testing()
add_subdirectory(tests)
