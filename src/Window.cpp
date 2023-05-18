#include "Window.h"

Window::Window(){ Setup("Window", sf::Vector2u(1920,1080)); }

Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
    Setup(l_title,l_size);
}

Window::~Window(){ Destroy(); }

void Window::Setup(const std::string l_title, const sf::Vector2u& l_size)
{
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen = true;
    m_isDone = false;
    Create();
}

void Window::Create()
{
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}

void Window::Destroy(){ m_window.close(); }

void Window::Update()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){m_isDone = true;}
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_isDone = true;
            }
        }
    }
}

void Window::BeginDraw(){ m_window.clear(sf::Color::Black); }

void Window::EndDraw(){ m_window.display(); }

bool Window::IsDone(){ return m_isDone; }

bool Window::IsFullscreen(){ return m_isFullscreen; }

sf::Vector2u Window::GetWindowSize(){ return m_windowSize; }

void Window::Draw(sf::Drawable& l_drawable)
{
    m_window.draw(l_drawable);
}

void Window::DrawBoard(Board& board)
{
    for (int i=0; board.getYSize()-1; i++)
    {
        for (int j=0; board.getXSize()-1; j++)
        {
            if (board.getObject(j,i) != board.getemptyFieldPtr())
            {
                std::shared_ptr<sf::Sprite> sprite_ptr = board.getObject(i,j)->GetSpritePtr();
                sprite_ptr->setPosition(sf::Vector2f(j*64.0f, i*64.0f));
                Draw(*sprite_ptr);
            }
        }
    }

}