#include "Game.h"
#include <SFML/System.hpp>

int main()
{
    // Program entry point.
    Game game;
    while(!game.GetWindow()->IsDone())
    {
        game.HandleInput();
        game.Update();
        game.Render();
    }
    return 0;
}