#ifndef H_RENDER_CORE_OBJECT_BASIC
#define H_RENDER_CORE_OBJECT_BASIC

#ifdef _MSC_VER> 1000
#pragma once
#endif

///< Shader has already include the drawObj.hpp
#include "d_render/core/shader.hpp"
#include "d_render/core/object/drawObj.hpp"

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

  static PlaneObject* getInstance();

 private:
  int m_GridInternal;

  REF(Shader) m_shader;
  static PlaneObject* m_instance;
};
}  // namespace renderer
}  // namespace daydream

#endif  // !H_RENDER_CORE_OBJECT_BASIC
