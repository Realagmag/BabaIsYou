#include <SFML/Graphics.hpp>
#include "Game.h"

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