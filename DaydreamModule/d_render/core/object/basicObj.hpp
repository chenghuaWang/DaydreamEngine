#ifndef H_RENDER_CORE_OBJECT_BASIC
#define H_RENDER_CORE_OBJECT_BASIC

#ifdef _MSC_VER> 1000
#pragma once
#endif

///< Shader has already include the drawObj.hpp
#include "d_render/core/shader.hpp"
#include "d_render/core/object/drawObj.hpp"

// Using Assimp to load models
#include "assimp/Importer.hpp"   // C++ importer interface
#include "assimp/scene.h"        // Output data structure
#include "assimp/postprocess.h"  // Post processing flags

namespace daydream {
namespace renderer {

/*!
 *@brief A Screen Space Shader. Mostly for Sky, fog, water, etc.
 * This act like a drawable class. Inherent from both Shader and
 * drawObj class.
 *
 * the draw function here is quite simple, just bind VAO to OpenGl,
 * and start to draw 2 triangles.
 */
class D_API_EXPORT ScreenSpaceShader : public Shader, public drawObject {
 public:
  ScreenSpaceShader(const std::string& all_src);
  ScreenSpaceShader(const std::string& name, const std::string& fragment_path);

  void initializeQuad();

 public:
  void draw() override;
  void update() override;

  void drawQuad();
  static void setDepthTest(bool enable);

 private:
  static bool m_inited;
  unsigned int quadVAO;
  unsigned int quadVBO;
};

/*!
 *@brie The plane object is just a flat.
 *
 * DLL EXPORT: True
 *
 * @details This object will shown by default in every 3d scene.
 * A speciall shader is working for it.
 * Like Screen space shader. The shader is managed by this class it-
 * self, and this class will only has one instance in the scene. Note
 * that, you are not recommand to use d_resource lib to manage the
 * shader belong to this class.
 */
class D_API_EXPORT PlaneObject : public drawObject {
 public:
  PlaneObject();

  void draw() override;
  void update() override;

  REF(Shader) & getShader() { return m_shader; }

  static PlaneObject* getInstance();

 private:
  int m_GridInternal;

  REF(Shader) m_shader;
  static PlaneObject* m_instance;
};

/*!
 *@brie The model object can load various files' type.
 *
 * DLL EXPORT: True
 */
class D_API_EXPORT ModelObject : public drawObject {
 public:
  ModelObject(){};
  ModelObject(const std::string& file_path);

  void draw() override;
  void update() override;

  MaterialType m_MaterialType = MaterialType::None;

 private:
  void __build_TBN__();
};

D_API_EXPORT bool __load_binary_files__(const std::string& file_path,
                                        std::vector<ModelObject*>& Meshes);

D_API_EXPORT void __process_node__(aiNode* node, const aiScene* scene,
                                   std::vector<ModelObject*>& Meshes);

D_API_EXPORT ModelObject* __process_mesh__(aiMesh* mesh, const aiScene* scene);

}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_OBJECT_BASIC
