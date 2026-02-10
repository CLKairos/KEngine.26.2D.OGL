#pragma once

#include "kengine/systems/system.hpp"

namespace kengine
{
namespace system
{
  class Speech : public System
  {
  public:
    Speech();
    void update (entt::registry& registry, const double dt) override;
  };
} // namespace system
} // namespace kengine
