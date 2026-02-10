#include "game.hpp"

#ifdef KENGINE_BUILD_EDITOR
  #include "editor/editor.hpp"
#endif

int main (int argc, char* argv[])
{
  nikte::Game game;

#ifdef KENGINE_BUILD_EDITOR
  kengine::editor::Editor editor{game};
  editor.run();
#else
  game.run();
#endif

  return 0;
}