#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "kengine/graphics/display.hpp"

typedef unsigned int GLuint;
typedef unsigned int GLenum;

namespace kengine
{
namespace graphics
{
  class Framebuffer
  {
  public:
    explicit Framebuffer (kengine::graphics::Display& display);
    ~Framebuffer();

    void Bind();
    static void Unbind();
    void Draw();

    void ActivateTexture (GLenum tex_id);
    inline GLuint GetTexture() const { return FBOtex; }

  private:
    GLuint FBO, FBOtex, VAO, VBO;
    kengine::graphics::Display& Display;
    glm::vec2 CurrentTextureResolution;

    void init();
    void RefreshTextureResolution();
  };
} // namespace graphics
} // namespace kengine
