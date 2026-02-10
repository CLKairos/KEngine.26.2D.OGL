#pragma once

#include "component.hpp"

namespace kengine
{
namespace component
{
  struct InGroup : public Component
  {
    InGroup() : Component ("In Group") {}
  };
} // namespace component
} // namespace kengine