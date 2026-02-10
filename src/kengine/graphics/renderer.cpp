#include "kengine/graphics/renderer.hpp"
#include "kengine/graphics/texture.hpp"
#include <vector>

namespace kengine
{
namespace graphics
{
  TexPtrs RendererT::m_textures = std::vector<std::shared_ptr<graphics::Texture>>();
}
} // namespace kengine