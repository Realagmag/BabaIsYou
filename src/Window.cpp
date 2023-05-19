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
    m_window.setKeyRepeatEnabled(false);
}

void Window::Create()
{
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({ m_windowSize.x, m_windowSize.y}, m_windowTitle, style);
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
            else if (event.key.code == sf::Keyboard::Up)
            {
                Action action = UP;
                _board->updateState(action);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                Action action = DOWN;
                _board->updateState(action);
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                Action action = LEFT;
                _board->updateState(action);
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                Action action = RIGHT;
                _board->updateState(action);
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
    for (int i=0; i < board.getYSize(); i++)
    {
        for (int j=0; j < board.getXSize(); j++)
        {
            if (board.getObject(j,i) != board.getemptyFieldPtr())
            {
                board.getObject(j,i)->GetSpritePtr()->setPosition(sf::Vector2f(float(j*60),float(i*60)));
                Draw(*board.getObject(j,i)->GetSpritePtr());
            }
        }
    }
}

void Window::SetBoardPtr(std::shared_ptr<Board> board_ptr)
{
    _board = board_ptr;
}