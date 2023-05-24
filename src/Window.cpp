#include "Window.h"

Window::Window(){ Setup("Window", sf::Vector2u(1920,1080)); }

Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
    Setup(l_title,l_size);
}

Window::~Window(){ Destroy(); }

void Window::Setup(const std::string l_title, const sf::Vector2u& l_size)
{
    _windowTitle = l_title;
    _windowSize = l_size;
    _isFullscreen = true;
    _isDone = false;
    Create();
    _window.setKeyRepeatEnabled(false);
}

void Window::Create()
{
    auto style = (_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    _window.create({ _windowSize.x, _windowSize.y}, _windowTitle, style);
}

void Window::Destroy(){ _window.close(); }

void Window::Update()
{
    sf::Event event;
    while(_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){_isDone = true;}
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                _isDone = true;
            }
        }
    }
}

void Window::BeginDraw(){ _window.clear(sf::Color::Black); }

void Window::EndDraw(){ _window.display(); }

bool Window::IsDone(){ return _isDone; }

bool Window::IsFullscreen(){ return _isFullscreen; }

sf::Vector2u Window::GetWindowSize(){ return _windowSize; }

void Window::Draw(sf::Drawable& l_drawable)
{
    _window.draw(l_drawable);
}

void Window::DrawBoard(Board& board)
{
    for (int i=0; i < board.getYSize(); i++)
    {
        for (int j=0; j < board.getXSize(); j++)
        {
            for (int k=0; k<board.getZSize(j,i); k++)
            {
                if (board.getObject(j,i,k) != board.getemptyFieldPtr())
                {
                    board.getObject(j,i,k)->GetSpritePtr()->setPosition(sf::Vector2f(float(j*60),float(i*60)));
                    Draw(*board.getObject(j,i,k)->GetSpritePtr());
                }
            }
        }
    }
}