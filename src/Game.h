#pragma once

#include <iostream>
#include "Window.h"
#include "Board.h"
#include "AudioManager.h"

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
    LOAD_WATERTEXT,
    LOAD_DEFEATTEXT,
    LOAD_FLOATTEXT,
    LOAD_HOTTEXT,
    LOAD_MELTTEXT,
    LOAD_PUSHTEXT,
    LOAD_SINKTEXT,
    LOAD_STOPTEXT,
    LOAD_WINTEXT,
    LOAD_YOUTEXT
};

class Game{
    public:
        Game(const Board &board);
        Game();
        ~Game();

        /** Handles player's keyboard input
         * Including: move action, choosing level, restart.*/
        void HandleInput();

        /** Handles events happening to window like closing it.*/
        void Update();

        /** Renders either game's menu or board if level has started.*/
        void Render();

        Window* GetWindow();

        unsigned int getCurrentLevel() const;

        void setCurrentLevel(unsigned int level_number);

    private:

        /** Fills board with ObjectOnFieldPtr depending on
         * current level. Deployment of pointers is coded
         * in LoadedLevels variable.*/
        void SetupBoard();

        /** Creates one entity of each ObjectOnField member,
         * loads their textures from files and creates sprite
         * for each object so it can be drawn in window.
         * Also load each ObjectOnField, Texture and sprite to
         * adequate vector.*/
        void CreateObjectInstances();

        /** Loads objects deployment for each level from .txt file.*/
        void LoadLevelsFromFile();

        /** Stores one entity of each ObjectOnField used in game
         * in order complementary with enum Loads.*/
        std::vector<ObjectOnField> AllObjects;

        /** Stores one sprite for each ObjectOnField used in game
         * so it can be drawn in window.*/
        std::vector<sf::Sprite> AllSprites;

        /** Stores texture of each sprite. This must be done because
         * sprite only gets pointer to texture.*/
        std::vector<sf::Texture> AllTexturesOfSprites;

        /** Stores shared pointers to each ObjectOnField used in game that
         * will be passed to board.*/
        std::vector<ObjectOnFieldPtr> AllObjectsPtrs;

        /** Stores objects deplopment for each level loaded from .txt file.*/
        std::vector<std::vector<std::vector<std::string>>> LoadedLevels;

        /**Manages window events and displays drawables*/
        Window _window;

        /**Holds objects' positions and manages game's logic*/
        Board _board;

        AudioManager _audio_manager;

        unsigned int _current_level;

        /** Flag used to prevent multiple actions while pressing key.*/
        bool IsKeyReleased = true;

        /** Flag used to change behaviour of program depending on whether
         * menu or level should be displayed.*/
        bool GameHasStarted = false;

        bool WinSoundWasPlayed = false;

        bool LoseSoundWasPlayed = false;
};
