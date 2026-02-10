#pragma once

#include "kengine/components/vertical.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Vertical
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine