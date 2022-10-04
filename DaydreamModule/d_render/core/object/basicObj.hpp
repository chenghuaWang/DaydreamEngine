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
class D_API_EXPORT KVBase;

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

class D_API_EXPORT LightsDrawObject : public drawObject {
 public:
  void draw() override final{};
  void update() override final{};

  void setCurLight(const _obj_light* lights){};

 private:
  _obj_light* m__lights;
  REF(Shader) m__shader;
};

/*!
 *@brief The sphare obejct is mostly for procedual SkyBox
 *
 * DLL EXPORT: True
 */
class D_API_EXPORT SphareObject : public drawObject {
 public:
  SphareObject(uint32_t scale = 0, uint32_t sample_step = 32);

  void draw() override;
  void update() override;
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

class D_API_EXPORT LineDrawObject : public drawObject {
 public:
  LineDrawObject();
  ~LineDrawObject();

  void draw() override;
  void update() override;

  void pushPoints(float sx, float sy, float sz, float ex, float ey, float ez, float r, float g,
                  float b);

 private:
  uint32_t m__vao = 0;
  uint32_t m__vbo = 0;
  uint32_t m__ibo = 0;
  REF(Shader) m__shader;
  void reBindData();
  float m__data[9] = {0};
  float m__index[2] = {0, 1};
};

D_API_EXPORT bool __load_binary_files__(const std::string& file_path,
                                        std::vector<ModelObject*>& Meshes, KVBase* db);

D_API_EXPORT void __process_node__(aiNode* node, const aiScene* scene,
                                   std::vector<ModelObject*>& Meshes, KVBase* db,
                                   const std::string& dir);

D_API_EXPORT ModelObject* __process_mesh__(aiMesh* mesh, const aiScene* scene, KVBase* db,
                                           const std::string& dir);

D_API_EXPORT REF(Texture2D)
    __load_texture__(aiMaterial* mat, aiTextureType type, const TEXTURE_TYPE& MyType, KVBase* db,
                     const std::string& dir);

}  // namespace renderer
}  // namespace daydream

namespace daydream {
namespace renderer {
enum class D_API_EXPORT ComponentType : uint8_t {
  None = 0,
  Texture_t,
  Material_t,
  Shader_t,
};

struct Component {
 protected:
  uint32_t __magic__ = 0;
  ComponentType __type__ = ComponentType::None;
};

struct ShaderComponent;
struct TextureComponent;
struct MaterialComponent;
struct ModelComponent;

struct TextureComponent : public Component {
  explicit TextureComponent(const REF(Texture2D) & a, const std::string& n, const std::string& f)
      : __this__(a), __name__(n), __file_path__(f) {
    __type__ = ComponentType::Texture_t;
  }

  const std::string& Name() const { return __name__; }
  const REF(Texture2D) & Item() const { return __this__; }

 private:
  std::string __name__;
  std::string __file_path__;
  REF(Texture2D) __this__;
};

struct ShaderComponent : public Component {
  explicit ShaderComponent(const REF(Shader) & a, const std::string& n, const std::string& f)
      : __this__(a), __name__(n), __file_path__(f) {
    __type__ = ComponentType::Shader_t;
  }

  const std::string& Name() const { return __name__; }
  const REF(Shader) & Item() const { return __this__; }

 private:
  std::string __name__;
  std::string __file_path__;
  REF(Shader) __this__;
};

struct MaterialComponent : public Component {
  explicit MaterialComponent(const REF(_obj_material) & a, const std::string& n)
      : __this__(a), __name__(n) {
    __type__ = ComponentType::Material_t;
  }

  const std::string& Name() const { return __name__; }
  const REF(_obj_material) & Item() const { return __this__; }
  void ApplyShader(const ShaderComponent& s) { __this__->SetShader(s.Item()); }

 private:
  std::string __name__;
  REF(_obj_material) __this__;
};

struct ModelComponent : public Component {
  explicit ModelComponent(std::vector<ModelObject*>& a, const std::string& name,
                          const std::string& f)
      : __this__(a), __name__(name), __file_path__(f) {}

  const std::string& Name() const { return __name__; }
  const std::vector<ModelObject*>& Item() const { return __this__; }
  void ApplyMaterialForAll(const MaterialComponent& m) {
    for (auto item : __this__) { item->m_defualt_material = m.Item(); }
  }

 private:
  std::string __name__;
  std::string __file_path__;
  std::vector<ModelObject*> __this__;
};

class D_API_EXPORT KVBase {
 public:
  ~KVBase();

  bool FindByPath(const std::string& f);

  void InsertTexture(const REF(Texture2D) & a, const std::string& name, const std::string& f);
  REF(Texture2D) FindTexture(const std::string& f);
  REF(Texture2D) FindTexture(uint32_t a);
  uint32_t TextureNum() const { return m_texture_index.size(); }

 private:
  uint32_t Hashing(const std::string& n);
  std::vector<uint32_t> m_texture_index;
  std::unordered_map<uint32_t, Component*> m_data;
};
}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_OBJECT_BASIC
