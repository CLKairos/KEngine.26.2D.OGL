#pragma once

#include "kengine/components/character_animation.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct CharacterAnimation
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine