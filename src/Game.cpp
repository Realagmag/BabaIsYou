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

void Game::SetupBoard()
{
    //For test purposes I manually create shared ptr to each object
    //It should be change to loop later
    CreateObjectInstances();
    ObjectOnFieldPtr baba_ptr = std::make_shared<ObjectOnField>(AllTypesOfObjects[0]);
    ObjectOnFieldPtr wall_ptr = std::make_shared<ObjectOnField>(AllTypesOfObjects[1]);
    _board.addObject(17,5,wall_ptr);
    _board.addObject(17,6,wall_ptr);
    _board.addObject(17,7,wall_ptr);
    _board.addObject(17,8,wall_ptr);
    _board.addObject(17,9,wall_ptr);
    _board.addObject(17,10,wall_ptr);
    _board.addObject(17,11,wall_ptr);
}

void Game::CreateObjectInstances()
{
    //For test purposes textures are simple shapes for now
    //Later it will be changes to load from files
    Baba baba;
    Wall wall;

    //Creating baba texture
    sf::CircleShape circle(64.0f);
    circle.setFillColor(sf::Color::Red);
    sf::RenderTexture circle_texture;
    circle_texture.create(64,64);
    circle_texture.clear();
    circle_texture.draw(circle);
    circle_texture.display();
    sf::Texture baba_texture = circle_texture.getTexture();

    //Creating wall texture
    sf::RectangleShape rectangle(sf::Vector2f(64.0f,64.0f));
    rectangle.setFillColor(sf::Color::Yellow);
    sf::RenderTexture rectangle_texture;
    rectangle_texture.create(64,64);
    rectangle_texture.clear();
    rectangle_texture.draw(rectangle);
    rectangle_texture.display();
    sf::Texture wall_texture = rectangle_texture.getTexture();

    baba.SetTexture(baba_texture);
    wall.SetTexture(wall_texture);

    AllTypesOfObjects.push_back(baba);
    AllTypesOfObjects.push_back(wall);
}