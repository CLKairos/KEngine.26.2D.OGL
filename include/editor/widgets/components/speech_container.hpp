#pragma once

#include "kengine/components/speech_container.hpp"
#include "imgui.h"

namespace kengine
{
namespace widget
{
  struct SpeechContainer
  {
    void operator() (entt::registry& registry, const entt::entity entity) {}
  };
} // namespace widget
} // namespace kengine