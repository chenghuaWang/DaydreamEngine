#include "shader.hpp"

namespace daydream {
namespace renderer {

bool ScreenSpaceShader::m_inited = false;

const std::string& ParseOneShader(const std::string& FilePath) {
  std::ifstream stream(FilePath);
  std::string line;
  std::stringstream ss;
  while (std::getline(stream, line)) { ss << line << "\n"; }
  return ss.str();
}

ShaderProgramSource ParseShader(const std::string& FilePath) {
  std::ifstream stream(FilePath);
  std::string line;
  std::stringstream ss[2];
  ShaderType Type = ShaderType::None;
  while (std::getline(stream, line)) {
    if (line.find("##shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        Type = ShaderType::Vertex;
      } else if (line.find("fragment") != std::string::npos) {
        Type = ShaderType::Fragment;
      }
    } else {
      ss[(int)Type - 1] << line << "\n";
    }
  }
  return {ss[0].str(), ss[1].str()};
}

unsigned int CompileShader(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* msg = (char*)malloc(length * sizeof(char));  //_malloca on win32 platform
    glGetShaderInfoLog(id, length, &length, msg);
    std::cout << "Failed to compile :" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
              << std::endl;
    std::cout << msg << std::endl;
    glDeleteShader(id);
  }
  return id;
}

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

Shader::Shader(const std::string& all_src) {
  ShaderProgramSource sps = ParseShader(all_src);

  uint32_t program_id = CreateShader(sps.VertexSource, sps.FragmentSource);
  m_idx = program_id;

  auto lastSlash = all_src.find_last_of("/\\");
  lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
  auto lastDot = all_src.rfind('.');
  auto count = lastDot == std::string::npos ? all_src.size() - lastSlash : lastDot - lastSlash;

  m_name = all_src.substr(lastSlash, count);
}

Shader::Shader(const std::string& name, const std::string& vertex_src,
               const std::string& fragment_src) {
  m_name = name;
  uint32_t program_id = CreateShader(vertex_src, fragment_src);
  m_idx = program_id;
}

Shader::~Shader() { glDeleteProgram(m_idx); }

void Shader::Bind() const { glUseProgram(m_idx); }

void Shader::UnBind() const { glUseProgram(0); }

const std::string& Shader::getName() const { return m_name; }

void Shader::setInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(m_idx, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(m_idx, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
  glUniform2fv(glGetUniformLocation(m_idx, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
  glUniform2f(glGetUniformLocation(m_idx, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
  glUniform3fv(glGetUniformLocation(m_idx, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(m_idx, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
  glUniform4fv(glGetUniformLocation(m_idx, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
  glUniform4f(glGetUniformLocation(m_idx, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const {
  glUniformMatrix2fv(glGetUniformLocation(m_idx, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
  glUniformMatrix3fv(glGetUniformLocation(m_idx, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(m_idx, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setBool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(m_idx, name.c_str()), (int)value);
}

std::shared_ptr<Shader> Shader::create(const std::string& all_src) {
  return CREATE_REF(Shader)(all_src);
}

std::shared_ptr<Shader> Shader::create(const std::string& name, const std::string& vertex_src,
                                       const std::string& fragment_src) {
  return CREATE_REF(Shader)(name, vertex_src, fragment_src);
}

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

}  // namespace renderer
}  // namespace daydream
