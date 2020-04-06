cmake_minimum_required(VERSION 3.5)
project(neotmux CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Curses REQUIRED)
find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(PROTOS
		${CMAKE_CURRENT_SOURCE_DIR}/proto/Multiplexer.proto
		${CMAKE_CURRENT_SOURCE_DIR}/proto/Interface.proto
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
		${GRPC_SRCS} source/Server.cpp source/Session.cpp source/Tab.cpp)

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
