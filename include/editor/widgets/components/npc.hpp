#pragma once

#include "kengine/components/npc.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct NPC
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine