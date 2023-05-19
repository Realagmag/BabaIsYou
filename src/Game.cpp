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
{}

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

    baba_texture.loadFromFile("../src/textures/Baba.png");
    baba_sprite.setTexture(baba_texture);

    baba_sprite.setScale(sf::Vector2f((64.0f/baba_texture.getSize().x),(64.0f/baba_texture.getSize().y)));

    wall_texture.loadFromFile("../src/textures/Wall.png");
    wall_sprite.setTexture(wall_texture);

    wall_sprite.setScale(sf::Vector2f((64.0f/wall_texture.getSize().x),(64.0f/wall_texture.getSize().y)));

    std::shared_ptr<sf::Sprite> baba_sprite_ptr = std::make_shared<sf::Sprite>(baba_sprite);
    std::shared_ptr<sf::Sprite> wall_sprite_ptr = std::make_shared<sf::Sprite>(wall_sprite);

    Baba baba;
    Wall wall;

    baba.SetSpritePtr(baba_sprite_ptr);
    wall.SetSpritePtr(wall_sprite_ptr);

    AllObjects.push_back(baba);
    AllObjects.push_back(wall);
}