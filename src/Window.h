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
        void Update();
        bool IsDone();
        bool IsFullscreen();
        sf::Vector2u GetWindowSize();
        void Draw(sf::Drawable& l_drawable);
        void DrawBoard(Board& board);

    private:
        void Setup(const std::string l_title, const sf::Vector2u& l_size);
        void Destroy();
        void Create();
        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        std::string m_windowTitle;
        bool m_isDone;
        bool m_isFullscreen;
};