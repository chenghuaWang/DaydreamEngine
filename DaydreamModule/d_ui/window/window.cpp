#include "window.hpp"

namespace daydream {
namespace ui {
    bool generate_glfw_context(){
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) return false;
        return true;
    }

    base_window::base_window(size_t w, size_t h, const std::string &window_name):
        m_W(w), m_H(h), m_window_name(window_name) {
        ///< init glfw context and imgui context.
        // init glfw context
        generate_glfw_context();

#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 330";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
        m_window_handle = glfwCreateWindow(m_W, m_H, m_window_name.c_str(), NULL, NULL);
        if (m_window_handle == NULL) exit(1);
        glfwMakeContextCurrent(m_window_handle);
        glfwSwapInterval(1); // Enable vsync
    }

    void base_window::flush() {
        ///< TODO flush function for only one frame update. Remember, only for graphics, not event.
    }

    void base_window::exec() {
        ///< TODO in exec, there is a render loop. Also a event loop. You should overload it.
    }
}
}