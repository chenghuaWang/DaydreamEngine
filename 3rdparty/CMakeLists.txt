# glm build static
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/glm")

# tiny objloader build static
add_library(tbl INTERFACE)
target_include_directories(tbl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/tinyobjloader")

# GLFW build static
add_subdirectory(GLFW)
set_property(TARGET glfw PROPERTY FOLDER "Extern/GLFW3/")
set_property(TARGET uninstall PROPERTY FOLDER "Extern/GLFW3/")

# spdlog
add_subdirectory(spdlog)
set_property(TARGET spdlog PROPERTY FOLDER "Extern/spdlog")

# glad build static
set(GLAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glad")
set(GLAD_FILES "${GLAD_DIR}/src/glad.c")
add_library(glad STATIC ${GLAD_FILES})
target_include_directories(glad PUBLIC ${GLAD_DIR} ${GLAD_DIR}/include)
set_property(TARGET glad PROPERTY FOLDER "Extern/")

# stb_image build static
set(STB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stb_image")
set(STB_FILES "${STB_DIR}/stb_image.cpp" "${STB_DIR}/stb_image.h")
add_library(stb_lib STATIC ${STB_FILES})
target_include_directories(stb_lib PUBLIC ${STB_DIR})
set_property(TARGET stb_lib PROPERTY FOLDER "Extern/")

# imgui build static
include_directories(${GLAD_DIR}/include)
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ImGui")
set(IMGUI_FILES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imconfig.h"
    "${IMGUI_DIR}/imgui.h"
    "${IMGUI_DIR}/imgui_internal.h"
    "${IMGUI_DIR}/imstb_rectpack.h"
    "${IMGUI_DIR}/imstb_textedit.h"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imstb_truetype.h"
    "${IMGUI_DIR}/imgui_impl_glfw.h"
    "${IMGUI_DIR}/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/imgui_impl_opengl3.h"
    "${IMGUI_DIR}/imgui_impl_opengl3.cpp"
    "${IMGUI_DIR}/ImGuizmo.cpp"
    "${IMGUI_DIR}/ImGuizmo.h"
    "${IMGUI_DIR}/TextEditor.h"
    "${IMGUI_DIR}/TextEditor.cpp"
    "${IMGUI_DIR}/ImGuiFileDialog.cpp"
    "${IMGUI_DIR}/ImGuiFileDialog.h"
    "${IMGUI_DIR}/ImGuiFileDialogConfig.h"
    "${IMGUI_DIR}/dirent/dirent.h"
)
add_library(imgui STATIC ${IMGUI_FILES})
target_link_libraries(imgui glfw)
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_FILES})
set_property(TARGET imgui PROPERTY FOLDER "Extern/")
