#pragma once

#include "system.hpp"
#include "kengine/components/body2d.hpp"
#include "kengine/topdown/world.hpp"

namespace kengine
{
namespace system
{
  class Physics : public System
  {
  private:
    const core::TileMap& m_tile_map;
    kengine::topdown::World m_world{m_tile_map};

  public:
    Physics (const core::TileMap& tile_map, entt::registry& registry);
    void update (entt::registry& registry, const double dt) override;

  private:
    Physics() = delete;
    void remove_body_from_world (entt::registry& registry, entt::entity entity);
    void initialize_body (entt::registry& registry, entt::entity entity);
  };
} // namespace system
} // namespace kengine
