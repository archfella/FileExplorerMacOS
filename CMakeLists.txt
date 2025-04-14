cmake_minimum_required(VERSION 3.10)
project(FileExplorerMacOS)

set(CMAKE_CXX_STANDARD 17)

# Set the path to third-party libraries
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/ImGui)
set(GLFW_DIR /usr/local/opt/glfw)

# Set the executable source file
add_executable(FileExplorerMacOS main.cpp
        h/IconFont.h
        src/TreeNode.cpp
        h/TreeNode.h
        src/FileTree.cpp
        h/FileTree.h
        src/TreeViewWindow.cpp
        h/TreeViewWindow.h
        src/SearchWindow.cpp
        h/SearchWindow.h
        src/IconViewWindow.cpp
        h/IconViewWindow.h
        src/DraggableIcon.cpp
        h/DraggableIcon.h
        h/IconTexturePaths.h
        src/LoadingWindow.cpp
        h/LoadingWindow.h
        src/ThemePrompt.cpp
        h/ThemePrompt.h)

# Defines the 'imgui' library.
add_library(imgui STATIC
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Include directories from 'imgui' library, including the backends.
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui PUBLIC ${IMGUI_DIR}/backends)


# Include directories for GLFW, needed by ImGui backend
target_include_directories(imgui PRIVATE ${GLFW_DIR}/include)

# GLFW
add_library(GLFW_Intergrated INTERFACE)
if (WIN32)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(GLFW_Intergrated INTERFACE glfw)
else ()
# Add ImGui and GLFW
    # This tells CMake to:
        # 1. Enter the GLFW directory.
        # 2. Find its CMakeLists.txt
        # 3. Build GLFW as part of our project.
    # *Find GLFW - This automatically finds the installed GLFW3 package, as it is installed system-wide (via: brew install glfw)
find_package(GLFW3 REQUIRED)
target_link_libraries(GLFW_Intergrated INTERFACE glfw)
endif ()

# GLEW
add_library(GLEW_Intergrated INTERFACE)
if (WIN32)
find_package(GLEW REQUIRED)
target_link_libraries(GLEW_Intergrated INTERFACE GLEW::GLEW)
else ()
# Add GLEW for OpenGL function loading
find_library(GLEW_LIBRARIES NAMES GLEW REQUIRED)
target_include_directories(GLEW_Intergrated INTERFACE ${GLEW_INCLUDE_DIRS})
target_link_libraries(GLEW_Intergrated INTERFACE ${GLEW_LIBRARIES})
endif ()

# OpenGL
add_library(OpenGL_Intergrated INTERFACE)
if (WIN32)
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL_Intergrated INTERFACE ${OPENGL_gl_LIBRARY})
else ()
# Link OpenGL (since it's required for your project)
find_library(OpenGL_LIBRARY OpenGL)
target_link_libraries(OpenGL_Intergrated INTERFACE ${OpenGL_LIBRARY})
endif ()

target_link_libraries(imgui PUBLIC GLFW_Intergrated)
target_link_libraries(imgui PUBLIC OpenGL_Intergrated)
target_link_libraries(imgui PUBLIC GLEW_Intergrated)

target_link_libraries(FileExplorerMacOS PRIVATE imgui)

# Include directories for FileExplorerMacOS
target_include_directories(FileExplorerMacOS PRIVATE ${GLFW_DIR}/include)
