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

        /** Handles events happening to window like closing it and
         * is updates sounds and music*/
        void Update();

        /** Renders either game's menu or board if level has started.*/
        void Render();

        Window* GetWindow();

        unsigned int getCurrentLevel() const;

        void setCurrentLevel(unsigned int level_number);

        /** Overloaded operator to enable easy data saving.*/
        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        /** Overloaded operator to enable easy data loading.*/
        friend std::istream& operator>>(std::istream& is, Game& game);

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

        /** Function used in the begining to highlight levels completed
         * in last run.*/
        void LoadProgressFromFile();

        /** Loads objects deployment for each level from .txt file.*/
        void LoadLevelsFromFile();

        /** Adds current level to list of completed levels*/
        void CountLevelAsComplited(unsigned int level);

        /** Saves numers of completed levels to file*/
        void SaveProgressToFile();

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

        /** Contains which levels have been completed*/
        std::vector<unsigned int> CompletedLevels;

        /** Manages window events and displays drawables*/
        Window _window;

        /** Holds objects' positions and manages game's logic*/
        Board _board;

        /** Manages all music and sound effects present in game*/
        AudioManager _audio_manager;

        unsigned int _current_level;

        /** Flag used to prevent multiple actions while pressing key.*/
        bool IsKeyReleased = true;

        /** Flag used to change behaviour of program depending on whether
         * menu or level should be displayed.*/
        bool GameHasStarted = false;

        /** Flag used to ensure that win sound will play only once*/
        bool WinSoundWasPlayed = false;

        /** Flag used to ensure that lose sound will play only once*/
        bool LoseSoundWasPlayed = false;
};
