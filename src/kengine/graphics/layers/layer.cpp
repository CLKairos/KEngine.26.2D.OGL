#include "kengine/graphics/layers/layer.hpp"

#include <iostream>
#include <algorithm>

namespace kengine
{
namespace graphics
{
  LayerT::LayerT (entt::registry& registry, const bool fixed) : m_registry (registry), fixed (fixed) {}
} // namespace graphics
} // namespace kengine