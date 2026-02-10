#pragma once

#include "kengine/components/shape.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Shape
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine