#pragma once

#include <iostream>
#include "Window.h"
#include "Board.h"


class Game{
    public:
        Game(const Board &board);
        Game();
        ~Game();
        void HandleInput();
        void Update();
        void Render();
        Window* GetWindow();
        Board _board;
        bool IsKeyReleased = true;

        std::vector<ObjectOnField> AllObjects;
        std::vector<sf::Sprite> AllSprites;
        std::vector<sf::Texture> AllTexturesOfSprites;

    private:
        void SetupBoard();
        void CreateObjectInstances();
        Window _window;
};
