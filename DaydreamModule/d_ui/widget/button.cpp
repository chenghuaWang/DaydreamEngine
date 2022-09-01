#include "button.hpp"

namespace daydream {
namespace ui {

button::button(const std::string& name) : m_name(name) {}

void button::impl_imgui_render() {
  if (ImGui::Button(m_name.c_str())) { click.Emit(); }
}

image_button::image_button(const std::string& name)
    : button(name), m_image_idx(0), m_image_size(0.f, 0.f) {
  result = nullptr;
}

image_button::~image_button() { glDeleteTextures(1, &m_image_idx); }

void image_button::impl_imgui_render() {
  if (ImGui::ImageButton((void*)m_image_idx, m_image_size)) { click.Emit(); }
}

void image_button::set_image(const std::string& path, float size_w, float size_h) {
  m_image_size.x = size_w;
  m_image_size.y = size_h;
  int nWidth = 0, nHeight = 0, nChannel = 0;
  result = stbi_load(path.c_str(), &nWidth, &nHeight, &nChannel, 4);
  if (result == NULL) {
    LOG_WARN("Can't load image for button.");
    return;
  }
  glGenTextures(1, &m_image_idx);
  glBindTexture(GL_TEXTURE_2D, m_image_idx);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, result);
  glGenerateMipmap(GL_TEXTURE_2D);
}

label::label(const std::string& name) : button(name) {}

void label::impl_imgui_render() { ImGui::LabelText(m_value.c_str(), m_name.c_str()); }

void label::set_value(const std::string& v) { m_value = v; }

}  // namespace ui
}  // namespace daydream
