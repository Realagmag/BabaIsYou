#include "Window.h"

Window::Window(){ Setup("Window", sf::Vector2u(1920,1080)); }

Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
    Setup(l_title,l_size);
    CreateMenuDrawables();
    SetupEndgameText();
}

Window::~Window(){ Destroy(); }

void Window::Setup(const std::string l_title, const sf::Vector2u& l_size)
{
    _number_of_levels = 8;
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

void Window::Update(bool& GameHasStarted)
{
    sf::Event event;
    while(_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){_isDone = true;}
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                if (GameHasStarted) GameHasStarted = false;
                else _isDone = true;
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

void Window::SetupEndgameText()
{
    std::string win_text = "Congratulations! Press Esc to go back to menu";
    std::string lose_text = "Press R to restart level";
    if(!font.loadFromFile("../src/fonts/ARIBL0.ttf")){
        std::cerr <<"Failed to load font" <<std::endl;
    }
    _win_text.setFont(font);
    _lose_text.setFont(font);
    _win_text.setString(win_text);
    _lose_text.setString(lose_text);

    _win_text.setCharacterSize(30);
    _win_text.setStyle(sf::Text::Bold);
    _win_text.setFillColor(sf::Color::Black);
    _win_text.setOutlineColor(sf::Color::Yellow);
    _win_text.setOutlineThickness(3);
    sf::FloatRect win_text_bounds = _win_text.getLocalBounds();
    _win_text.setOrigin(win_text_bounds.left + win_text_bounds.width/2.0f,
                        win_text_bounds.top + win_text_bounds.height/2.0f);
    _win_text.setPosition(_windowSize.x/2, 64);

    _lose_text.setCharacterSize(30);
    _lose_text.setStyle(sf::Text::Bold);
    _lose_text.setFillColor(sf::Color::Black);
    _lose_text.setOutlineColor(sf::Color::Red);
    _lose_text.setOutlineThickness(3);
    sf::FloatRect lose_text_bounds = _lose_text.getLocalBounds();
    _lose_text.setOrigin(lose_text_bounds.left + lose_text_bounds.width/2.0f,
                        lose_text_bounds.top + lose_text_bounds.height/2.0f);
    _lose_text.setPosition(_windowSize.x/2, 64);

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
                    board.getObject(j,i,k)->GetSpritePtr()->setPosition(sf::Vector2f(float(j*64),float(i*66)));
                    Draw(*board.getObject(j,i,k)->GetSpritePtr());
                }
            }
        }
    }
}

void Window::DrawWin()
{
    Draw(_win_text);
}

void Window::DrawLose()
{
    Draw(_lose_text);
}

void Window::CreateMenuDrawables()
{
    for (int i=0; i < _number_of_levels; i++)
    {
        sf::Texture texture;
        std::string number = std::to_string(i+1);
        if(!texture.loadFromFile("../src/textures/level_"+number+".png"))
        {
            std::cout << "Failed to load texture for level " << number << std::endl;
        }
        levels_textures.emplace_back(texture);
        sf::Sprite sprite;

        sprite.setPosition(sf::Vector2f((_windowSize.x/10)*(i+1)+32, (_windowSize.y/6)*4));
        levels_sprites.emplace_back(sprite);
    }
    _choose_level_texture.loadFromFile("../src/textures/choose_level.png");
    _choose_level_sprite.setTexture(_choose_level_texture);
    sf::Vector2u size = _choose_level_texture.getSize();
    _choose_level_sprite.setOrigin(size.x/2, size.y/2);
    _choose_level_sprite.setScale(sf::Vector2f(3,3));
    _choose_level_sprite.setPosition(sf::Vector2f(_windowSize.x/2, _windowSize.y/4));
    red_level.setSize(sf::Vector2f(127,55));
    red_level.setFillColor(sf::Color::Red);
}

void Window::DrawMenu(int current_level)
{
    float rectangle_xpos = _windowSize.x/10*(current_level+1) + 32;
    float rectangle_ypos = _windowSize.y/6*4 + 20;
    red_level.setPosition(sf::Vector2f(rectangle_xpos, rectangle_ypos));
    Draw(red_level);
    Draw(_choose_level_sprite);
    for (int i= 0; i < _number_of_levels; i++)
    {
        levels_sprites[i].setTexture(levels_textures[i]);
        Draw(levels_sprites[i]);
    }


}