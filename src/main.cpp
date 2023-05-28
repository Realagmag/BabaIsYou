#include "Game.h"

int main()
{
    Game game; //Create game instance, window and board.
    while(!game.GetWindow()->IsDone())
    {
        game.HandleInput(); //Handle player's input.
        game.Update(); //Update window events.
        game.Render(); //Draw on screen.
    }
    return 0;
}