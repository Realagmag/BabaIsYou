#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"

class Window{
    public:
        Window();
        Window(const std::string& l_title,const sf::Vector2u& l_size);
        ~Window();
        void BeginDraw(); // Clear the window.
        void EndDraw(); // Display the changes.
        void Update(bool& GameHasStarted);
        bool IsDone();
        bool IsFullscreen();
        sf::Vector2u GetWindowSize();
        void Draw(sf::Drawable& l_drawable);
        void DrawBoard(Board& board);
        void DrawMenu();
        int _number_of_levels;
        std::vector<sf::Texture> levels_textures;
        std::vector<sf::Sprite> levels_sprites;
        sf::Texture _choose_level_texture;
        sf::Sprite _choose_level_sprite;

    private:
        void CreateMenuDrawables();
        void Setup(const std::string l_title, const sf::Vector2u& l_size);
        void Destroy();
        void Create();
        sf::RenderWindow _window;
        sf::Vector2u _windowSize;
        std::string _windowTitle;
        bool _isDone;
        bool _isFullscreen;
};