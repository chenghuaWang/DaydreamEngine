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

ModelObject::ModelObject(const std::string& file_path) {}

void ModelObject::draw() {
  auto m_shader = m_defualt_material->GetShader();
  // bind the shader
  m_shader->Bind();
  // bind the data before shader setup
  DRAW_DATA_INIT
  // pass the MVP matrix
  m_shader->setMat4("d_ViewProjection", renderPayload->mainCamera->getViewProjectionMatrix());
  m_shader->setMat4("d_Transform", this->Transform());
  m_shader->UnBind();
}

void ModelObject::update() {}

void ModelObject::__build_TBN__() {
  // This function is no need any more when using Assimp and CalcTangentSpace flag is open.
  // But it stil keeped, for tinyobjloader and self phaser class.
  return;
}

bool __load_binary_files__(const std::string& file_path, std::vector<ModelObject*>& Meshes) {
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

  // Now we can access the file's contents.
  __process_node__(scene->mRootNode, scene, Meshes);

  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}

void __process_node__(aiNode* node, const aiScene* scene, std::vector<ModelObject*>& Meshes) {
  // Reference from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/model.h
  // process each mesh located at the current node
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    // the node object only contains indices to index the actual objects in the scene.
    // the scene contains all the data, node is just to keep stuff organized (like relations between
    // nodes).
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    Meshes.push_back(__process_mesh__(mesh, scene));
  }
  // after we've processed all of the meshes (if any) we then recursively process each of the
  // children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    __process_node__(node->mChildren[i], scene, Meshes);
  }
}

ModelObject* __process_mesh__(aiMesh* mesh, const aiScene* scene) {
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
  return __tmp_mesh__;
}

}  // namespace renderer
}  // namespace daydream