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
  m_instance = this;
}

void PlaneObject::draw() {
  // BackGround
  glDisable(GL_CULL_FACE);
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

ModelObject::ModelObject(const std::string& file_path) {}

void ModelObject::draw() {
  // Enabel Back
  glEnable(GL_CULL_FACE);
  auto m_shader = m_defualt_material->GetShader();
  // bind the shader
  m_defualt_material->Bind();
  // bind the data before shader setup
  DRAW_DATA_INIT
  // pass the MVP matrix
  m_shader->setMat4("d_ViewProjection", renderPayload->mainCamera->getViewProjectionMatrix());
  m_shader->setMat4("d_Transform", this->Transform());
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
                                       | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

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
  // Judge if this material is belongs to witted style BRDF Only.
  auto __diffuse_cnt__ = material->GetTextureCount(aiTextureType_DIFFUSE);
  auto __specular_cnt__ = material->GetTextureCount(aiTextureType_SPECULAR);
  auto __normal_cnt__ = material->GetTextureCount(aiTextureType_HEIGHT);
  auto __ambient_cnt__ = material->GetTextureCount(aiTextureType_AMBIENT);
  auto __aot_cnt__ = material->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION);
  auto __displament_cnt__ = material->GetTextureCount(aiTextureType_DISPLACEMENT);
  auto __metallic_cnt__ = material->GetTextureCount(aiTextureType_METALNESS);
  if (__aot_cnt__ != 0) {
    // Can use brdf
  } else {
    REF(MaterialPhong) __tmp_material__ = CREATE_REF(MaterialPhong)();
    if (__diffuse_cnt__) {
      __tmp_material__->resetDiffuseTexture(
          __load_texture__(material, aiTextureType_DIFFUSE, TEXTURE_TYPE::Diffuse, db, dir));
    }
    if (__specular_cnt__) {
      __tmp_material__->resetSpecularTexture(
          __load_texture__(material, aiTextureType_SPECULAR, TEXTURE_TYPE::Specular, db, dir));
    }
    if (__normal_cnt__) {
      __tmp_material__->resetNormalTexture(
          __load_texture__(material, aiTextureType_HEIGHT, TEXTURE_TYPE::Normal, db, dir));
    }
    if (__displament_cnt__) {
      __tmp_material__->resetDisplacementTexture(__load_texture__(
          material, aiTextureType_DISPLACEMENT, TEXTURE_TYPE::Displacement, db, dir));
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