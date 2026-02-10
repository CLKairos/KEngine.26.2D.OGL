#include "player.hpp"
#include <kengine/graphics/display.hpp>
#ifdef _WIN32
  #include <SDL.h>
#else
  #include <SDL2/SDL.h> // IWYU pragma: export
#endif
#undef main
#include <iostream>

Player::Player (entt::registry& registry, kengine::graphics::Display& display) : m_registry (registry), Display (display)
{
}

void Player::update()
{
  auto& body = m_registry.get<kengine::component::Body2D> (entity);

  if (this->Display.IsKeyDown (SDL_SCANCODE_UP))
  {
    body.Body->MoveTop();
  }

  if (this->Display.IsKeyDown (SDL_SCANCODE_DOWN))
  {
    body.Body->MoveBottom();
  }

  if (this->Display.IsKeyDown (SDL_SCANCODE_LEFT))
  {
    body.Body->MoveLeft();
  }

  if (this->Display.IsKeyDown (SDL_SCANCODE_RIGHT))
  {
    body.Body->MoveRight();
  }

  if (m_registry.has<kengine::component::AnimationPlayer> (entity))
  {
    auto& anims = m_registry.get<kengine::component::AnimationPlayer> (entity);
    this->SetState (body, anims);
  }
}

void Player::SetState (const kengine::component::Body2D& body, kengine::component::AnimationPlayer& anims)
{
  std::string animation_name = "";
  switch (body.Body->state)
  {
    case kengine::topdown::BodyState::IDLE:
      animation_name.append ("idle-");
      break;
    case kengine::topdown::BodyState::MOVING:
      animation_name.append ("walking-");
      break;
    default:
      break;
  }

  // If we have defined a animation (BodyState is IDLE or MOVING)
  if (!animation_name.empty())
  {
    if (body.Body->direction & kengine::topdown::BodyDirection::LEFT)
    {
      animation_name.append (1, 'l');
    }
    else if (body.Body->direction & kengine::topdown::BodyDirection::RIGHT)
    {
      animation_name.append (1, 'r');
    }
    else if (body.Body->direction & kengine::topdown::BodyDirection::TOP)
    {
      animation_name.append (1, 't');
    }
    else if (body.Body->direction & kengine::topdown::BodyDirection::BOTTOM)
    {
      animation_name.append (1, 'b');
    }
    anims.current = animation_name;
  }
}
