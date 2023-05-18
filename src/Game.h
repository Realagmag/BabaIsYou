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
        std::vector<ObjectOnField> AllTypesOfObjects;

    private:
        void SetupBoard();
        void CreateObjectInstances();
        Window m_window;
};
