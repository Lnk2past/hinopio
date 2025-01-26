add_executable(hinopio hinopio.cpp)

target_include_directories(hinopio PUBLIC "${CMAKE_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(hinopio PUBLIC GLEW::GLEW glfw fmt::fmt nlohmann_json::nlohmann_json)
