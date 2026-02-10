#pragma once

#include "kengine/components/movement.hpp"
#include "kengine/components/player.hpp"
#include "kengine/components.hpp"
#include "./system.hpp"

namespace kengine
{
namespace system
{
  class Movement : public System
  {
  public:
    Movement() {}

    ~Movement() override {}

    void update (entt::registry& registry, const double dt) override
    {
      registry
          .group<component::Movement> (entt::get<component::Position>,
                                       entt::exclude<component::Body2D, component::Player>)
          .each ([&dt] (auto entity, auto& mov, auto& pos) {
            pos.x += mov.TargetVelocity.x * dt;
            pos.y += mov.TargetVelocity.y * dt;
          });
    }
  };
} // namespace system
} // namespace kengine
