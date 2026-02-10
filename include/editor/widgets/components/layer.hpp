#pragma once

#include "kengine/components/layer.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Layer
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine