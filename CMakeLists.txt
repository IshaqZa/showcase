cmake_minimum_required(VERSION "3.10")
Project(tryout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build")

add_executable(tryout
    main.cpp
    Actions.cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/imp/GameScene.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imp/GameObject.cpp"
)
target_include_directories(tryout PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(tryout PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/libOpenUI.a"
)

find_package(GLFW3 REQUIRED)
target_link_libraries(tryout PRIVATE glfw)

