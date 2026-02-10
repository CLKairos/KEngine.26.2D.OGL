#pragma once

#include "kengine/components/script.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Script
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine