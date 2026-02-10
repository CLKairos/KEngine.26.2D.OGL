#pragma once

#include <kengine/components/body2d.hpp>
#include <kengine/components/animation_player.hpp>
#include <entt/entity/registry.hpp> // IWYU pragma: export

namespace kengine
{
namespace graphics
{
  class Display;

}
} // namespace kengine

class Player
{
public:
  entt::registry& m_registry;
  enum State
  {
    IDLE,
    WALKING
  };
  const entt::registry::entity_type entity = m_registry.create();

private:
  kengine::graphics::Display& Display;
  State current_state = IDLE;
  char direction      = 'd'; // Direction to which the player is facing (u, d, l, r)

public:
  Player (entt::registry& registry, kengine::graphics::Display& display);
  void update();

private:
  void SetState (const kengine::component::Body2D& body, kengine::component::AnimationPlayer& anims);
};
