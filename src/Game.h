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

        std::vector<ObjectOnField> AllObjects;
        std::vector<sf::Sprite> AllSprites;
        std::vector<sf::Texture> AllTexturesOfSprites;

        sf::Texture baba_texture;
        sf::Sprite baba_sprite;
        sf::Texture wall_texture;
        sf::Sprite wall_sprite;

    private:
        void SetupBoard();
        void CreateObjectInstances();
        Window m_window;
};
