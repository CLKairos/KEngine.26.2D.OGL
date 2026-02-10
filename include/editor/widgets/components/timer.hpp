#pragma once

#include "kengine/components/timer.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Timer
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine