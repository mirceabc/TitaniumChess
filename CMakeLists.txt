cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(TitaniumChess VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

if(APPLE)

    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/macOS/${CMAKE_BUILD_TYPE})
    set(MACOSX_BUNDLE_ICON_FILE TitaniumChess.icns)
    set(TITANIUM_CHESS_ICON ${CMAKE_CURRENT_SOURCE_DIR}/assets/icons/TitaniumChess.icns)
    set_source_files_properties(${TITANIUM_CHESS_ICON} 
    PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    add_executable(TitaniumChess MACOSX_BUNDLE ${TITANIUM_CHESS_ICON}
        src/glad.c
        src/main.cpp
        src/input/InputManager.cpp
        
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/backends/imgui_impl_opengl3.cpp
        include/imgui/backends/imgui_impl_glfw.cpp
    )

    set_target_properties(TitaniumChess PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/resources/macOS/Info.plist
    )

    add_custom_command(
    TARGET TitaniumChess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_BINARY_DIR}/build/TitaniumChess.app
        ${CMAKE_SOURCE_DIR}/bin/macOS/${CMAKE_BUILD_TYPE}/TitaniumChess.app
    COMMENT "Copying TitaniumChess.app to bin directory"
    )
endif(APPLE)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_include_directories(TitaniumChess PRIVATE include/) # TitaniumChess
target_include_directories(TitaniumChess PRIVATE include/imgui) # ImGui

if(APPLE)
    target_link_libraries(TitaniumChess "-framework Cocoa")
    target_link_libraries(TitaniumChess "-framework OpenGL")
    target_link_libraries(TitaniumChess "-framework IOKit")
endif(APPLE)
    target_link_libraries(TitaniumChess glfw glm::glm ${OPENGL_gl_LIBRARY})