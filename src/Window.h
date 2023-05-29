#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Parameters.h"

class Window{
    public:
        Window();
        Window(const std::string& l_title,const sf::Vector2u& l_size);
        ~Window();

        /** Clears the window*/
        void BeginDraw();

        /** Displays the changes*/
        void EndDraw();

        /** Updates window events*/
        void Update(bool& GameHasStarted);

        /** Checks if window should be closed*/
        bool IsDone() const;

        /** Checks if window should be displayed
         * in fullscreen mode*/
        bool IsFullscreen() const;

        /** Returns window x and y size*/
        sf::Vector2u GetWindowSize() const;

        /** Draws every object in current board in correct position*/
        void DrawBoard(const Board& board);

        /** Draws text saying about win*/
        void DrawWin();

        /** Draws text in case of game is lost*/
        void DrawLose();

        /** Draws game's menu where player can choose level*/
        void DrawMenu(int current_level, const std::vector<unsigned int> &completed_levels);





    private:

        /** Creates instances of sprites and shapes used in game's menu
         * And sets their size and postion*/
        void CreateMenuDrawables();

        /** Sets window's title and size*/
        void Setup(const std::string l_title, const sf::Vector2u& l_size);

        /** Creates text that are displayed in the end of the game:
         * win_text in case of winning,
         * lose_text in case of losing.*/
        void SetupEndgameText();

        /** Closes the window*/
        void Destroy();

        /** Creates instance of SFML sf::RenderWindow class*/
        void Create();

        /** Used to display any drawable SFML object*/
        void Draw(const sf::Drawable& l_drawable);

        /** SFML window class and it's parameters*/
        sf::RenderWindow _window;
        sf::Vector2u _windowSize;
        std::string _windowTitle;

        /** SFML drawable text classes that can be modified and customized*/
        sf::Text _win_text;
        sf::Text _lose_text;

        /** SFML class that enables using a custom font*/
        sf::Font _font;

        /** Objects that are displayed in game's menu*/
        std::vector<sf::Texture> levels_textures;
        std::vector<sf::Sprite> levels_sprites;
        sf::Texture _choose_level_texture;
        sf::Sprite _choose_level_sprite;
        sf::RectangleShape _red_level; //used to highlight level that will be loaded after pressing enter.

        /** Flag that checks if window should be closed*/
        bool _isDone;

        /** Flag that checks if window should be displayed in fullscreen mode*/
        bool _isFullscreen;
};
