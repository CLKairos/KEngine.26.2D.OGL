#pragma once

#include "component.hpp"

namespace kengine
{
namespace component
{
  struct Camera : public Component
  {
    Camera() : Component ("Camera") {}
    uint8_t id = 0;
  };
} // namespace component
} // namespace kengine
