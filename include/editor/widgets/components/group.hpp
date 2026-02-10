#pragma once

#include "kengine/components/group.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Group
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine