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

    /********************************************************************/
    /* under for window_base implementaion */
    window_base::window_base(size_t w, size_t h, const std::string& window_name) :
        m_W(w), m_H(h), m_window_name(window_name), m_logger(new p_logger("./info.log")) {
        // init glfw context
        if (!generate_glfw_context()) {
            LOG_ERROR("Create glfw context error !!!")
            exit(1);
        }

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
        // GL 3.0 + GLSL 330
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

    window_base::~window_base() {
        if (m_window_handle) {
            glfwDestroyWindow(m_window_handle);
            collect_glfw_context();
        }
    }

    void window_base::hook_glfw_callback() {
        glfwSetWindowCloseCallback(m_window_handle, on_window_close);
        glfwSetWindowSizeCallback(m_window_handle, on_window_resize);
    }

    void window_base::on_window_resize(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void window_base::on_window_close(GLFWwindow* window) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void window_base::exec() {
        this->hook_glfw_callback();
        while (!glfwWindowShouldClose(m_window_handle)) {
            glfwPollEvents();
            
            flush_frame();
            update_event();

            glClearColor(1.0, 0.0, 1.0, 0.3);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(m_window_handle);
            glfwDestroyWindow(m_window_handle);
            collect_glfw_context();
        }
    }

    void window_base::flush_frame() {

    }

    void window_base::update_event() {

    }

    size_t window_base::getW() {
        return m_W;
    }

    size_t window_base::getH() {
        return m_H;
    }

    /********************************************************************/
    /* under for imgui_window implementaion */
    imgui_window::imgui_window(size_t w, size_t h, uint16_t flags, const std::string& window_name) : 
        window_base(w, h, window_name), 
        m_window_flags(flags) {
        generate_imgui_context();

        // LOGGING basic infomation
        LOG_INFO("Start initialize window with size (w x h)= " + std::to_string(w) + " x " + std::to_string(h));
        LOG_INFO("Loading dynamic libs...done.");
    }

    imgui_window::~imgui_window() {
        LOG_INFO("Exit window...done.");
    }

    void imgui_window::_imgui_start_() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuizmo::BeginFrame();
        ImGuizmo::Enable(true);

        static bool p_open = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
            window_flags |= ImGuiWindowFlags_NoBackground;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &p_open, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen) {
            ImGui::PopStyleVar(2);
        }

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
    }

    void imgui_window::_imgui_end_() {
        /*Docking Space*/
        ImGui::End();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)m_W, (float)m_H);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void imgui_window::set_imgui_style(imgui_color_style style) {
        switch (style) {
        case imgui_color_style::CLASSIC_DARK:
            ImGui::StyleColorsDark();
            break;
        case imgui_color_style::CLASSIC_WHITE:
            ImGui::StyleColorsLight();
            break;
        default:
            ImGui::StyleColorsClassic();
            break;
        }
    }

    void imgui_window::exec() {
        LOG_INFO("Starting to execute window.")
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        if (m_window_flags & imgui_window_flags::DOCKING) {
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        }
        if ((m_window_flags >> 1) & imgui_window_flags::MULTI_WINDOW) {
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        this->set_imgui_style(imgui_color_style::CLASSIC_DARK);
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        ImGui_ImplGlfw_InitForOpenGL(m_window_handle, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        this->hook_glfw_callback();
        while (!glfwWindowShouldClose(m_window_handle)) {
            glfwPollEvents();

            _imgui_start_();
            flush_frame();
            _imgui_end_();

            update_event();

            glfwSwapBuffers(m_window_handle);
        }

        LOG_INFO("Destroy IMGUI context...done.")
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void imgui_window::flush_frame() {
    }

    void imgui_window::update_event() {
    }

}
}