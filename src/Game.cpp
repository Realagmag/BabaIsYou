#include "Game.h"
#include "./SolidObjects/Baba.h"
#include "./SolidObjects/Wall.h"
#include "./SolidObjects/Flag.h"
#include "./SolidObjects/Lava.h"
#include "./SolidObjects/Rock.h"
#include "./SolidObjects/Skull.h"
#include "./SolidObjects/Tree.h"
#include "./SolidObjects/Water.h"

Game::Game(const Board &board)
: _board(board) {}

Game::Game(): _window("Baba is You", sf::Vector2u(1920,1080)), _board(30, 16)
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
    _window.Update(); // Update window events.
}

void Game::Render()
{
    _window.BeginDraw(); // Clear.
    _window.DrawBoard(_board);
    _window.EndDraw(); // Display.
}

Window* Game::GetWindow()
{
    return &_window;
}

void Game::SetupBoard()
{
    //For test purposes I manually create shared ptr to each object
    //It should be change to loop later
    CreateObjectInstances();
    ObjectOnFieldPtr baba_ptr = std::make_shared<ObjectOnField>(AllObjects[0]);
    baba_ptr->isYou = true;
    ObjectOnFieldPtr flag_ptr = std::make_shared<ObjectOnField>(AllObjects[1]);
    ObjectOnFieldPtr lava_ptr = std::make_shared<ObjectOnField>(AllObjects[2]);
    ObjectOnFieldPtr rock_ptr = std::make_shared<ObjectOnField>(AllObjects[3]);
    ObjectOnFieldPtr skull_ptr = std::make_shared<ObjectOnField>(AllObjects[4]);
    ObjectOnFieldPtr tree_ptr = std::make_shared<ObjectOnField>(AllObjects[5]);
    ObjectOnFieldPtr wall_ptr = std::make_shared<ObjectOnField>(AllObjects[6]);
    ObjectOnFieldPtr water_ptr = std::make_shared<ObjectOnField>(AllObjects[7]);
    _board.addObject(10,10,baba_ptr);
    _board.addObject(17,5,wall_ptr);
    _board.addObject(17,6,wall_ptr);
    _board.addObject(17,7,wall_ptr);
    _board.addObject(17,9,wall_ptr);
    _board.addObject(17,10,wall_ptr);
    _board.addObject(17,11,wall_ptr);
    _board.addObject(17,12,wall_ptr);
    _board.addObject(18,12,wall_ptr);
    _board.addObject(19,12,wall_ptr);
    _board.addObject(20,12,wall_ptr);
    _board.addObject(21,12,wall_ptr);
    _board.addObject(22,12,wall_ptr);
    _board.addObject(22,11,wall_ptr);
    _board.addObject(22,10,wall_ptr);
    _board.addObject(22,9,wall_ptr);
    _board.addObject(22,8,wall_ptr);
    _board.addObject(22,7,wall_ptr);
    _board.addObject(22,6,wall_ptr);
    _board.addObject(22,5,wall_ptr);
    _board.addObject(21,5,wall_ptr);
    _board.addObject(20,5,wall_ptr);
    _board.addObject(19,5,wall_ptr);
    _board.addObject(18,5,wall_ptr);
    _board.addObject(16,7,tree_ptr);
    _board.addObject(16,9,tree_ptr);
    _board.addObject(3,0,water_ptr);
    _board.addObject(3,1,water_ptr);
    _board.addObject(3,2,water_ptr);
    _board.addObject(3,3,water_ptr);
    _board.addObject(2,3,water_ptr);
    _board.addObject(1,3,water_ptr);
    _board.addObject(0,3,water_ptr);
    _board.addObject(1,1,flag_ptr);
    _board.addObject(4,0,lava_ptr);
    _board.addObject(4,1,lava_ptr);
    _board.addObject(4,2,lava_ptr);
    _board.addObject(4,3,lava_ptr);
    _board.addObject(7,0,skull_ptr);
    _board.addObject(7,1,skull_ptr);
    _board.addObject(7,2,skull_ptr);
    _board.addObject(8,0,skull_ptr);
    _board.addObject(9,0,skull_ptr);
    _board.addObject(10,0,skull_ptr);
    _board.addObject(11,0,skull_ptr);
    _board.addObject(11,1,skull_ptr);
    _board.addObject(11,2,skull_ptr);
    _board.addObject(14,8,rock_ptr);
    _board.addObject(11,4,rock_ptr);
    _board.addObject(14,12,rock_ptr);
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

    Flag flag;
    AllObjects.emplace_back(flag);
    sf::Texture flag_texture;
    AllTexturesOfSprites.emplace_back(flag_texture);
    sf::Sprite flag_sprite;
    AllSprites.emplace_back(flag_sprite);

    Lava lava;
    AllObjects.emplace_back(lava);
    sf::Texture lava_texture;
    AllTexturesOfSprites.emplace_back(lava_texture);
    sf::Sprite lava_sprite;
    AllSprites.emplace_back(lava_sprite);

    Rock rock;
    AllObjects.emplace_back(rock);
    sf::Texture rock_texture;
    AllTexturesOfSprites.emplace_back(rock_texture);
    sf::Sprite rock_sprite;
    AllSprites.emplace_back(rock_sprite);

    Skull skull;
    AllObjects.emplace_back(skull);
    sf::Texture skull_texture;
    AllTexturesOfSprites.emplace_back(skull_texture);
    sf::Sprite skull_sprite;
    AllSprites.emplace_back(skull_sprite);

    Tree tree;
    AllObjects.emplace_back(tree);
    sf::Texture tree_texture;
    AllTexturesOfSprites.emplace_back(tree_texture);
    sf::Sprite tree_sprite;
    AllSprites.emplace_back(tree_sprite);

    Wall wall;
    AllObjects.emplace_back(wall);
    sf::Texture wall_texture;
    AllTexturesOfSprites.emplace_back(wall_texture);
    sf::Sprite wall_sprite;
    AllSprites.emplace_back(wall_sprite);

    Water water;
    AllObjects.emplace_back(water);
    sf::Texture water_texture;
    AllTexturesOfSprites.emplace_back(water_texture);
    sf::Sprite water_sprite;
    AllSprites.emplace_back(water_sprite);



    for (int i; i < AllObjects.size(); i++)
    {
        AllTexturesOfSprites[i].loadFromFile(AllObjects[i].getImagePath());
        AllSprites[i].setTexture(AllTexturesOfSprites[i]);
        AllSprites[i].setScale(sf::Vector2f((64.0f/AllTexturesOfSprites[i].getSize().x),(64.0f/AllTexturesOfSprites[i].getSize().y)));
        AllObjects[i].SetSpritePtr(std::make_shared<sf::Sprite>(AllSprites[i]));
    }
}