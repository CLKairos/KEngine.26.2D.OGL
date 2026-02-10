#pragma once

#include "kengine/systems/system.hpp"

namespace kengine
{
namespace system
{
  class Timer : public System
  {
  public:
    Timer (entt::registry& registry);
    void update (entt::registry& registry, const double dt) override;

  private:
    Timer() = delete;
  };
} // namespace system
} // namespace kengine
