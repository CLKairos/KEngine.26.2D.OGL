#pragma once

#include "kengine/components/color.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Color
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine