add_executable(UnitTests
        main.cpp
        Window.cpp)

target_include_directories(UnitTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(UnitTests PRIVATE Catch2::Catch2)

add_test(NAME UnitTests COMMAND UnitTests)