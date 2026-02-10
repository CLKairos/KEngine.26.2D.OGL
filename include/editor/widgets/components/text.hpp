#pragma once

#include "kengine/components/text.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct Text
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine