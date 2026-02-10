#pragma once

#include <kengine/kengine.hpp>  // IWYU pragma: export
#include <kengine/systems.hpp> // IWYU pragma: export
#include <kengine/core/tile_map.hpp>
#include <kengine/perlin.hpp>

// #ifdef KENGINE_BUILD_EDITOR
//   #include <editor/editor.h>
//   #include <editor/widgets/map_editor.h>
// #endif

#include "player.hpp"

#ifdef KENGINE_BUILD_EDITOR
namespace kengine
{
namespace editor
{
  class Editor;
}
namespace widget
{
  class MapEditor;
}
} // namespace kengine
#endif

namespace nikte
{
class Game : public kengine::core::Game
{
private:
  Player m_player{m_registry, m_display};
  kengine::core::TileMap m_tile_map{m_registry};
  // kengine::core::TileMap m_tile_map{"scripts/demo/church_map.xml", m_registry};
  // kengine::PerlinNoise m_perlin_generator{47};
  // std::default_random_engine m_generator;
  // std::uniform_real_distribution<double> m_perlin_distribution{0.0,1.0};
  // std::uniform_int_distribution<int> m_flower_frame_distribution{0,3};

#ifdef KENGINE_BUILD_EDITOR
  friend class kengine::editor::Editor;
  friend class kengine::widget::MapEditor;
#endif

public:
  Game();
  ~Game();

private:
  void update (const double dt) override;
  void render (const double dt) override;
  void m_load_flowers();
  void m_load_flower (const int x, const int y);
  // entt::registry::entity_type create_player();
  // void update_player(const double dt);
};
} // namespace nikte
