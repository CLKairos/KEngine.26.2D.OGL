#pragma once

#include "component.hpp"

namespace kengine
{
namespace component
{
  struct Charcode : public Component
  {
    Charcode() : Component ("charcode") {}
    Charcode (wchar_t c) : Component ("Charcode"), code (c) {}
    wchar_t code = 0;
  };
} // namespace component
} // namespace kengine
