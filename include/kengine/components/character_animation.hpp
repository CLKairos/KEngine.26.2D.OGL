#pragma once

#include "component.hpp"

namespace kengine
{
namespace component
{
  struct CharacterAnimation : public Component
  {
    CharacterAnimation() : Component ("Character Animation") {}
    int place_holder = 0;
  };
} // namespace component
} // namespace kengine
