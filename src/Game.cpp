#include "Game.h"
#include "./SolidObjects/Baba.h"
#include "./SolidObjects/Wall.h"

Game::Game(const Board &board)
: _board(board) {}

Game::Game(): m_window("Baba is You", sf::Vector2u(1920,1080)), _board(30, 16)
{
    SetupBoard();
}

Game::~Game(){}

void Game::HandleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && IsKeyReleased)
    {
        IsKeyReleased = false;
        Action action = UP;
        _board.updateState(action);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && IsKeyReleased)
    {
        IsKeyReleased = false;
        Action action = LEFT;
        _board.updateState(action);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && IsKeyReleased)
    {
        IsKeyReleased = false;
        Action action = DOWN;
        _board.updateState(action);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && IsKeyReleased)
    {
        IsKeyReleased = false;
        Action action = RIGHT;
        _board.updateState(action);
    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
    !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        IsKeyReleased = true;
    }
}

void Game::Update()
{
    m_window.Update(); // Update window events.
}

void Game::Render()
{
    m_window.BeginDraw(); // Clear.
    m_window.DrawBoard(_board);
    m_window.EndDraw(); // Display.
}

Window* Game::GetWindow()
{
    return &m_window;
}

void Game::SetupBoard()
{
    //For test purposes I manually create shared ptr to each object
    //It should be change to loop later
    CreateObjectInstances();
    ObjectOnFieldPtr baba_ptr = std::make_shared<ObjectOnField>(AllObjects[0]);
    baba_ptr->isYou = true;
    ObjectOnFieldPtr wall_ptr = std::make_shared<ObjectOnField>(AllObjects[1]);
    _board.addObject(10,8,baba_ptr);
    _board.addObject(17,5,wall_ptr);
    _board.addObject(17,6,wall_ptr);
    _board.addObject(17,7,wall_ptr);
    _board.addObject(17,9,wall_ptr);
    _board.addObject(17,10,wall_ptr);
    _board.addObject(17,11,wall_ptr);
    _board.addObject(3,0,wall_ptr);
}

void Game::CreateObjectInstances()
{
    // Creates Textures, Sprites and ObjectOnField instances and stores it
    Baba baba;
    AllObjects.emplace_back(baba);
    sf::Texture baba_texture;
    AllTexturesOfSprites.emplace_back(baba_texture);
    sf::Sprite baba_sprite;
    AllSprites.emplace_back(baba_sprite);

    Wall wall;
    AllObjects.emplace_back(wall);
    sf::Texture wall_texture;
    AllTexturesOfSprites.emplace_back(wall_texture);
    sf::Sprite wall_sprite;
    AllSprites.emplace_back(wall_sprite);

    for (int i; i < AllObjects.size(); i++)
    {
        AllTexturesOfSprites[i].loadFromFile(AllObjects[i].getImagePath());
        AllSprites[i].setTexture(AllTexturesOfSprites[i]);
        AllSprites[i].setScale(sf::Vector2f((64.0f/AllTexturesOfSprites[i].getSize().x),(64.0f/AllTexturesOfSprites[i].getSize().y)));
        AllObjects[i].SetSpritePtr(std::make_shared<sf::Sprite>(AllSprites[i]));
    }
}