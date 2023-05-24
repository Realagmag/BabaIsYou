#pragma once

#include <iostream>
#include "Window.h"
#include "Board.h"

enum Load
{
    LOAD_BABA,
    LOAD_FLAG,
    LOAD_LAVA,
    LOAD_ROCK,
    LOAD_SKULL,
    LOAD_TREE,
    LOAD_WALL,
    LOAD_WATER,
    LOAD_IS,
    LOAD_AND,
    LOAD_BABATEXT,
    LOAD_FLAGTEXT,
    LOAD_LAVATEXT,
    LOAD_ROCKTEXT,
    LOAD_SKULLTEXT,
    LOAD_TREETEXT,
    LOAD_WALLTEXT,
    LOAD_WATERTEXT
};

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

        //Order of objects: Baba, Flag, Lava, Rock, Skull, Tree, Wall, Water
        std::vector<ObjectOnField> AllObjects;
        std::vector<sf::Sprite> AllSprites;
        std::vector<sf::Texture> AllTexturesOfSprites;
        std::vector<ObjectOnFieldPtr> AllObjectsPtrs;

        std::vector<std::vector<std::string>> LoadedObjects;

    private:
        void SetupBoard();
        void CreateObjectInstances();
        Window _window;
};
