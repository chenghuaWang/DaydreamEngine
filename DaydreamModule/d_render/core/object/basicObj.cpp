#include "basicObj.hpp"

namespace daydream {
namespace renderer {

bool ScreenSpaceShader::m_inited = false;

ScreenSpaceShader::ScreenSpaceShader(const std::string& all_src)
    : Shader("no-name", SCREEN_SPACE_SHADER_VERT_SRC, all_src) {
  initializeQuad();
}

ScreenSpaceShader::ScreenSpaceShader(const std::string& name, const std::string& fragment_path)
    : Shader(name, SCREEN_SPACE_SHADER_VERT_SRC, ParseOneShader(fragment_path)) {
  initializeQuad();
}

void ScreenSpaceShader::initializeQuad() {
  if (!m_inited) {
    float vertices[] = {-1.0f, -1.0f, 0.0, 0.0, 1.0f,  -1.0f, 1.0, 0.0, -1.0f, 1.0f,  0.0, 1.0,
                        1.0f,  1.0f,  1.0, 1.0, -1.0f, 1.0f,  0.0, 1.0, 1.0f,  -1.0f, 1.0, 0.0};

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    ScreenSpaceShader::m_inited = true;
  }
}

void ScreenSpaceShader::draw() {
  // TODO bind shader ?
  drawQuad();
}

void ScreenSpaceShader::update() {}

void ScreenSpaceShader::drawQuad() {
  glBindVertexArray(quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ScreenSpaceShader::setDepthTest(bool enable) {
  if (enable) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

PlaneObject* PlaneObject::m_instance = nullptr;

PlaneObject::PlaneObject() {
  m_shader = Shader::create("../Asset/shader/PlaneObj.glsl");
  uint32_t sample = 256;
  for (uint32_t i = 0; i <= sample; i++) {
    for (uint32_t j = 0; j <= sample; j++) {
      Vertex v;
      v.m_Position = {(float)i / (float)sample - 0.5f, 0.0f, (float)j / (float)sample - 0.5f};
      v.m_Normal = {0.0f, 1.0f, 0.0f};
      v.m_TexCoord = {(float)i / (float)sample, (float)j / (float)sample};
      m_vertex.push_back(v);
    }
  }
  uint32_t indices[6] = {0, sample + 1, sample + 2, 0, sample + 2, 1};

  for (int k = 0; k < (sample + 1) * sample; k++)
    for (int i = 0; i < 6; i++)
      if ((k + 1) % (sample + 1) > 0) m_Index.push_back(indices[i] + k);

  for (size_t i = 0; i < m_Index.size(); i += 3) {
    Triangle triangle = {m_Index[i], m_Index[i + 1ul], m_Index[i + 2ul]};
    m_triangle.push_back(triangle);
  }
  genVertexArray();
  m_instance = this;
}

void PlaneObject::draw() {
  // bind the shader
  m_shader->Bind();
  // bind the data before shader setup
  DRAW_DATA_INIT
  // pass the MVP matrix
  m_shader->setMat4("d_ViewProjection", renderPayload->mainCamera->getViewProjectionMatrix());
  m_shader->setMat4("d_Transform", this->Transform());
  m_shader->UnBind();
}

void PlaneObject::update() {}

PlaneObject* PlaneObject::getInstance() { return m_instance; }

}  // namespace renderer
}  // namespace daydream