#pragma once

#include <string>

namespace kengine
{
namespace component
{
  struct Component
  {
    Component (const std::string& name) : name (name) {}
    std::string name = "";
    bool loaded = false;
  };
} // namespace component
} // namespace kengine