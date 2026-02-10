#pragma once

#include "entt/entity/fwd.hpp"
#include "system.hpp"

namespace kengine
{
namespace system
{
  class CharacterAnimation : public System
  {
  public:
    CharacterAnimation();
    void update (entt::registry& registry, const double dt) override;
  };
} // namespace system
} // namespace kengine
