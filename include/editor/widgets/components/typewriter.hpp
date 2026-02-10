#pragma once

#include "kengine/components/typewriter.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Typewriter
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine