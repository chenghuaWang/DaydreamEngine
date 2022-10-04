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
  uint32_t sample = 64;
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

  for (uint32_t k = 0; k < (sample + 1) * sample; k++)
    for (uint32_t i = 0; i < 6; i++)
      if ((k + 1) % (sample + 1) > 0) m_Index.push_back(indices[i] + k);

  for (size_t i = 0; i < m_Index.size(); i += 3) {
    Triangle triangle = {m_Index[i], m_Index[i + 1ul], m_Index[i + 2ul]};
    m_triangle.push_back(triangle);
  }
  genVertexArray();
  m_Scale = {100.f, 100.f, 100.f};
  m_instance = this;
}

void PlaneObject::draw() {
  // BackGround
  glDisable(GL_CULL_FACE);
  // bind the shader
  m_shader->Bind();
  // pass the MVP matrix
  m_shader->setMat4("d_ViewProjection", renderPayload->mainCamera->getViewProjectionMatrix());
  m_shader->setMat4("d_Transform", this->Transform());
  m_shader->setInt("d_scale", 32);
  // bind the data after shader setup
  DRAW_DATA_INIT
  m_shader->UnBind();
}

void PlaneObject::update() {}

PlaneObject* PlaneObject::getInstance() { return m_instance; }

SphareObject::SphareObject(uint32_t scale, uint32_t sample_step) {
  uint32_t real = sample_step * 10;
  for (uint32_t i = 0; i <= real; i++)
    for (uint32_t j = 0; j <= real; j++) {
      Vertex v;
      v.m_Position = {(float)i / (float)real, 0.0f, (float)j / (float)real};
      v.m_Normal = {0.0f, 1.0f, 0.0f};
      v.m_TexCoord = {(float)i / (float)real, (float)j / (float)real};
      m_vertex.push_back(v);
    }
  uint32_t indices[6] = {0, real + 1, real + 2, 0, real + 2, 1};
  for (uint32_t k = 0; k < (real + 1) * real; k++)
    for (uint32_t i = 0; i < 6; i++)
      if ((k + 1) % (real + 1) > 0) m_Index.push_back(indices[i] + k);
  for (size_t i = 0; i < m_Index.size(); i += 3) {
    Triangle triangle = {m_Index[i], m_Index[i + 1ul], m_Index[i + 2ul]};
    m_triangle.push_back(triangle);
  }
  for (auto& p : m_vertex) {
    float phi = glm::radians(360.0f * p.m_Position.z);
    float theta = glm::radians(180.0f * p.m_Position.x - 90.0f);
    p.m_Position.x = p.m_Normal.x = cos(theta) * cos(phi);
    p.m_Position.y = p.m_Normal.y = sin(theta);
    p.m_Position.z = p.m_Normal.z = cos(theta) * sin(phi);
  }
  genVertexArray();
}

void SphareObject::draw() {}

void SphareObject::update() {}

ModelObject::ModelObject(const std::string& file_path) {}

void ModelObject::draw() {
  // Enabel Back
  glEnable(GL_CULL_FACE);
  auto m_shader = m_defualt_material->GetShader();
  // bind the shader
  m_defualt_material->Bind();
  // pass the MVP matrix
  m_shader->setMat4("d_ViewProjection", renderPayload->mainCamera->getViewProjectionMatrix());
  m_shader->setMat4("d_Transform", this->Transform());
  m_shader->setVec3("d_camPos", this->renderPayload->mainCamera->getPosition());
  // bind the data after shader setup
  DRAW_DATA_INIT;
  m_defualt_material->UnBind();
}

void ModelObject::update() {}

void ModelObject::__build_TBN__() {
  // This function is no need any more when using Assimp and CalcTangentSpace flag is open.
  // But it stil keeped, for tinyobjloader and self phaser class.
  return;
}

bool __load_binary_files__(const std::string& file_path, std::vector<ModelObject*>& Meshes,
                           KVBase* db) {
  // Reference from https://assimp-docs.readthedocs.io/en/v5.1.0/usage/use_the_lib.html
  // Create an instance of the Importer class
  Assimp::Importer importer;

  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // probably to request more postprocessing than we do in this example.
  const aiScene* scene =
      importer.ReadFile(file_path, aiProcess_CalcTangentSpace | aiProcess_Triangulate
                                       | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
                                       | aiProcess_ImproveCacheLocality | aiProcess_OptimizeMeshes
                                       | aiProcess_PreTransformVertices);

  // If the import failed, report it
  if (nullptr == scene) {
    LOG_ERROR(importer.GetErrorString());
    return false;
  }

  auto directory = file_path.substr(0, file_path.find_last_of('\\'));

  // Now we can access the file's contents.
  __process_node__(scene->mRootNode, scene, Meshes, db, directory);

  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}

void __process_node__(aiNode* node, const aiScene* scene, std::vector<ModelObject*>& Meshes,
                      KVBase* db, const std::string& dir) {
  // Reference from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/model.h
  // process each mesh located at the current node
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    // the node object only contains indices to index the actual objects in the scene.
    // the scene contains all the data, node is just to keep stuff organized (like relations between
    // nodes).
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    Meshes.push_back(__process_mesh__(mesh, scene, db, dir));
  }
  // after we've processed all of the meshes (if any) we then recursively process each of the
  // children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    __process_node__(node->mChildren[i], scene, Meshes, db, dir);
  }
}

ModelObject* __process_mesh__(aiMesh* mesh, const aiScene* scene, KVBase* db,
                              const std::string& dir) {
  // Reference from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/model.h
  // data to fill
  auto __tmp_mesh__ = new ModelObject();
  auto __tmp_vertex__ = &__tmp_mesh__->m_vertex;
  auto __tmp_index__ = &__tmp_mesh__->m_Index;
  // walk through each of the mesh's vertices
  glm::vec3 vector;
  for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;
    // positions
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.m_Position = vector;
    // normals
    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.m_Normal = vector;
    }
    // texture coordinates
    if (mesh->mTextureCoords[0]) {  // does the mesh contain texture coordinates?
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.m_TexCoord = vec;
      // tangent
      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.m_Tangent = vector;
      // bitangent
      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.m_Bitangent = vector;
    } else {
      vertex.m_Tangent = glm::vec2(0.0f, 0.0f);
    }
    __tmp_vertex__->push_back(vertex);
  }
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      __tmp_index__->push_back(face.mIndices[j]);
    }
  }
  __tmp_mesh__->genVertexArray();
  // Load material for texture
  aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
  // Some Payload need for material.
  aiString ai_mat_name;
  aiBlendMode ai_mat_blend_mode;
  // A new way to load materials The original method below is dropped but also contained
  if (AI_SUCCESS != material->Get(AI_MATKEY_NAME, ai_mat_name)) {}
  if (AI_SUCCESS != material->Get(AI_MATKEY_BLEND_FUNC, ai_mat_blend_mode)) {
    std::cout << "No Blend Mode Found\n";
  }
  // Judge if this material is belongs to witted style BRDF Only.

  auto __diffuse_cnt__ = material->GetTextureCount(aiTextureType_DIFFUSE);
  auto __normal_cnt__ = material->GetTextureCount(aiTextureType_HEIGHT);
  auto __aot_cnt__ = material->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION);
  auto __displament_cnt__ = material->GetTextureCount(aiTextureType_DISPLACEMENT);
  auto __metallic_cnt__ = material->GetTextureCount(aiTextureType_METALNESS);
  auto __basecolor_cnt__ = material->GetTextureCount(aiTextureType_BASE_COLOR);
  if (__aot_cnt__ != 0) {
    // Can use brdf
  } else {
    REF(MaterialBRDF) __tmp_material__ = CREATE_REF(MaterialBRDF)();
    if (__diffuse_cnt__) {
      __tmp_material__->resetAlbedoTexture(
          __load_texture__(material, aiTextureType_DIFFUSE, TEXTURE_TYPE::Diffuse, db, dir));
    }
    if (__basecolor_cnt__) {
      __tmp_material__->resetAlbedoTexture(
          __load_texture__(material, aiTextureType_BASE_COLOR, TEXTURE_TYPE::BaseColor, db, dir));
    }
    if (__normal_cnt__) {
      __tmp_material__->resetNormalTexture(
          __load_texture__(material, aiTextureType_HEIGHT, TEXTURE_TYPE::Normal, db, dir));
    }
    if (__displament_cnt__) {
      __tmp_material__->resetDisplacementTexture(__load_texture__(
          material, aiTextureType_DISPLACEMENT, TEXTURE_TYPE::Displacement, db, dir));
    }
    if (__metallic_cnt__) {
      __tmp_material__->resetMetallicTexture(
          __load_texture__(material, aiTextureType_METALNESS, TEXTURE_TYPE::Metallic, db, dir));
    }
    __tmp_mesh__->m_defualt_material = __tmp_material__;
  }
  return __tmp_mesh__;
}

D_API_EXPORT REF(Texture2D)
    __load_texture__(aiMaterial* mat, aiTextureType type, const TEXTURE_TYPE& MyType, KVBase* db,
                     const std::string& dir) {
  aiString str;
  mat->GetTexture(type, 0,
                  &str);  // TODO, I suppose there is juts one Texture for one mesh in one kind.
  auto __tmp_file_path__ = dir + "\\" + str.C_Str();
  if (db->FindByPath(__tmp_file_path__)) { return db->FindTexture(__tmp_file_path__); }
  std::cout << " Loading Texture " << __tmp_file_path__ << std::endl;
  auto __texture_tmp__ = CREATE_REF(Texture2D)(__tmp_file_path__);
  db->InsertTexture(__texture_tmp__, "No Name", __tmp_file_path__);
  return __texture_tmp__;
}

LineDrawObject::LineDrawObject() : m__shader(CREATE_REF(Shader)("../Asset/shader/Lines.glsl")) {}

LineDrawObject::~LineDrawObject() {
  // free all opengl buffers.
  // Delete VAO
  glDeleteVertexArrays(1, &m__vao);
  // Delete VBO
  glDeleteBuffers(1, &m__vbo);
  // Delete IBO
  glDeleteBuffers(1, &m__ibo);
}

void LineDrawObject::draw() {
  glm::vec4 s = {m__data[0], m__data[1], m__data[2], 1.0};
  glm::vec4 e = {m__data[3], m__data[4], m__data[5], 1.0};
  s = renderPayload->mainCamera->getViewProjectionMatrix() * s;
  e = renderPayload->mainCamera->getViewProjectionMatrix() * e;
}

void LineDrawObject::update() {}

void LineDrawObject::pushPoints(float sx, float sy, float sz, float ex, float ey, float ez, float r,
                                float g, float b) {
  m__data[0] = sx;
  m__data[1] = sy;
  m__data[2] = sz;
  m__data[3] = ex;
  m__data[4] = ey;
  m__data[5] = ez;
  m__data[6] = r;
  m__data[7] = g;
  m__data[8] = b;
  reBindData();
}

void LineDrawObject::reBindData() {
  // ReProcess VAO
  glCreateVertexArrays(1, &m__vao);
  // ReProcess VBO
  glCreateBuffers(1, &m__vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m__vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 6, m__data, GL_DYNAMIC_DRAW);
  // ReProcess IBO
  BufferLayout __layout__ = {
      {ElementType::Vecf3, "a_Position"},
  };
  // Bind VBO to VAO
  glBindVertexArray(m__vao);
  glBindBuffer(GL_ARRAY_BUFFER, m__vbo);
  if (__layout__.GetElements().size() == 0) {
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    LOG_ERROR("The VerexBuffer don't have correct Layout!");
    return;
  }
  uint32_t _index = 0;
  for (const auto& element : __layout__) {
    glEnableVertexAttribArray(_index);
    glVertexAttribPointer(_index, 3, GL_FLOAT, element.Normalized ? GL_TRUE : GL_FALSE,
                          __layout__.GetStride(), (const void*)(element.Offset));
    _index++;
  }
  // Create IDO
  glCreateBuffers(1, &m__ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m__ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(uint32_t), m__index, GL_STATIC_DRAW);
  // Bind IDO to VAO
  glBindVertexArray(m__vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m__ibo);
}

}  // namespace renderer
}  // namespace daydream

namespace daydream {
namespace renderer {
KVBase::~KVBase() {
  for (auto item : m_data) { delete item.second; }
}

bool KVBase::FindByPath(const std::string& f) {
  auto it = m_data.find(Hashing(f));
  if (it != m_data.end()) { return true; }
  return false;
}

void KVBase::InsertTexture(const REF(Texture2D) & a, const std::string& name,
                           const std::string& f) {
  if (FindByPath(f)) { return; }
  uint32_t t = Hashing(f);
  m_data[t] = new TextureComponent(a, name, f);
  m_texture_index.push_back(t);
}

REF(Texture2D) KVBase::FindTexture(const std::string& f) {
  if (FindByPath(f)) { return static_cast<TextureComponent*>(m_data[Hashing(f)])->Item(); }
  return nullptr;
}

REF(Texture2D) KVBase::FindTexture(uint32_t a) {
  return static_cast<TextureComponent*>(m_data[m_texture_index[a]])->Item();
}

uint32_t KVBase::Hashing(const std::string& n) {
  std::hash<std::string> HashString;
  return HashString(n);
}
}  // namespace renderer
}  // namespace daydream