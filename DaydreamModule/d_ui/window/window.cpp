#include "window.hpp"

namespace daydream {
namespace ui {
    bool generate_glfw_context() {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) return false;
        return true;
    }

    void generate_imgui_context() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
    }

    void collect_glfw_context() {
        glfwTerminate();
    }

    void collect_imgui_context() {
        ImGui::DestroyContext();
    }

    base_window::base_window(size_t w, size_t h, const std::string &window_name):
        m_W(w), m_H(h), m_window_name(window_name) {
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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
        m_window_handle = glfwCreateWindow(m_W, m_H, m_window_name.c_str(), NULL, NULL);
        if (m_window_handle == NULL) exit(1);
        glfwMakeContextCurrent(m_window_handle);
        glfwSwapInterval(1); // Enable vsync

        // init imgui context
        generate_imgui_context();
        this->set_global_style();
    }

    void base_window::flush() {
        ///< TODO flush function for render a new frame and update event every loop.
    }

    void base_window::exec() {
        ImGui_ImplGlfw_InitForOpenGL(m_window_handle, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        int display_w, display_h;

        while (!glfwWindowShouldClose(m_window_handle)) {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                flush(); 
            }

            ImGui::Render();
            glfwGetFramebufferSize(m_window_handle, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_window_handle);
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        collect_imgui_context();
        glfwDestroyWindow(m_window_handle);
        collect_glfw_context();
    }

    void base_window::set_global_style() {
        ImGui::StyleColorsDark();
    }
}
}