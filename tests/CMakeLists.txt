add_executable(UnitTests
        main.cpp
        Window.cpp util/MockServer.cpp Client.cpp Server.cpp)

target_include_directories(UnitTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(UnitTests PRIVATE Catch2::Catch2
        ntmux_core)

add_test(NAME UnitTests COMMAND UnitTests)