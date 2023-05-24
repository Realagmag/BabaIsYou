#include "Game.h"
#include <fstream>
#include "./SolidObjects/Baba.h"
#include "./SolidObjects/Wall.h"
#include "./SolidObjects/Flag.h"
#include "./SolidObjects/Lava.h"
#include "./SolidObjects/Rock.h"
#include "./SolidObjects/Skull.h"
#include "./SolidObjects/Tree.h"
#include "./SolidObjects/Water.h"
#include "./Noun.h"
#include "./Operator.h"
#include "./Property.h"

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


    AllObjectsPtrs[LOAD_BABA]->setProperty("You", true);
    _board.addObject(5,10,AllObjectsPtrs[LOAD_BABA]);
    _board.addObject(10,10,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(17,5,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(17,6,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(17,7,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(17,9,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(17,10,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(17,11,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(17,12,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(18,12,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(19,12,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(20,12,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(21,12,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,12,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,11,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,10,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,9,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,8,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,7,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,6,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(22,5,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(21,5,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(20,5,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(19,5,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(18,5,AllObjectsPtrs[LOAD_WALL]);
    _board.addObject(16,7,AllObjectsPtrs[LOAD_TREE]);
    _board.addObject(16,9,AllObjectsPtrs[LOAD_TREE]);
    _board.addObject(3,0,AllObjectsPtrs[LOAD_WATER]);
    _board.addObject(3,1,AllObjectsPtrs[LOAD_WATER]);
    _board.addObject(3,2,AllObjectsPtrs[LOAD_WATER]);
    _board.addObject(3,3,AllObjectsPtrs[LOAD_WATER]);
    _board.addObject(2,3,AllObjectsPtrs[LOAD_WATER]);
    _board.addObject(1,3,AllObjectsPtrs[LOAD_WATER]);
    _board.addObject(0,3,AllObjectsPtrs[LOAD_WATER]);
    _board.addObject(1,1,AllObjectsPtrs[LOAD_FLAG]);
    _board.addObject(4,0,AllObjectsPtrs[LOAD_LAVA]);
    _board.addObject(4,1,AllObjectsPtrs[LOAD_LAVA]);
    _board.addObject(4,2,AllObjectsPtrs[LOAD_LAVA]);
    _board.addObject(4,3,AllObjectsPtrs[LOAD_LAVA]);
    _board.addObject(7,0,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(7,1,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(7,2,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(8,0,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(9,0,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(10,0,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(11,0,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(11,1,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(11,2,AllObjectsPtrs[LOAD_SKULL]);
    _board.addObject(14,8,AllObjectsPtrs[LOAD_ROCK]);
    _board.addObject(11,4,AllObjectsPtrs[LOAD_ROCK]);
    _board.addObject(14,12,AllObjectsPtrs[LOAD_ROCK]);
    _board.addObject(6,10,AllObjectsPtrs[LOAD_IS]);
    _board.addObject(6,11,AllObjectsPtrs[LOAD_BABATEXT]);
    _board.addObject(6,12,AllObjectsPtrs[LOAD_AND]);
    _board.addObject(7,12,AllObjectsPtrs[LOAD_WALLTEXT]);
    _board.addObject(8,12,AllObjectsPtrs[LOAD_TREETEXT]);
    _board.addObject(9,12,AllObjectsPtrs[LOAD_ROCKTEXT]);
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
    ObjectOnFieldPtr baba_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_BABA]);
    AllObjectsPtrs.emplace_back(baba_ptr);

    Flag flag;
    AllObjects.emplace_back(flag);
    sf::Texture flag_texture;
    AllTexturesOfSprites.emplace_back(flag_texture);
    sf::Sprite flag_sprite;
    AllSprites.emplace_back(flag_sprite);
    ObjectOnFieldPtr flag_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_FLAG]);
    AllObjectsPtrs.emplace_back(flag_ptr);

    Lava lava;
    AllObjects.emplace_back(lava);
    sf::Texture lava_texture;
    AllTexturesOfSprites.emplace_back(lava_texture);
    sf::Sprite lava_sprite;
    AllSprites.emplace_back(lava_sprite);
    ObjectOnFieldPtr lava_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_LAVA]);
    AllObjectsPtrs.emplace_back(lava_ptr);

    Rock rock;
    AllObjects.emplace_back(rock);
    sf::Texture rock_texture;
    AllTexturesOfSprites.emplace_back(rock_texture);
    sf::Sprite rock_sprite;
    AllSprites.emplace_back(rock_sprite);
    ObjectOnFieldPtr rock_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_ROCK]);
    AllObjectsPtrs.emplace_back(rock_ptr);

    Skull skull;
    AllObjects.emplace_back(skull);
    sf::Texture skull_texture;
    AllTexturesOfSprites.emplace_back(skull_texture);
    sf::Sprite skull_sprite;
    AllSprites.emplace_back(skull_sprite);
    ObjectOnFieldPtr skull_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_SKULL]);
    AllObjectsPtrs.emplace_back(skull_ptr);

    Tree tree;
    AllObjects.emplace_back(tree);
    sf::Texture tree_texture;
    AllTexturesOfSprites.emplace_back(tree_texture);
    sf::Sprite tree_sprite;
    AllSprites.emplace_back(tree_sprite);
    ObjectOnFieldPtr tree_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_TREE]);
    AllObjectsPtrs.emplace_back(tree_ptr);

    Wall wall;
    AllObjects.emplace_back(wall);
    sf::Texture wall_texture;
    AllTexturesOfSprites.emplace_back(wall_texture);
    sf::Sprite wall_sprite;
    AllSprites.emplace_back(wall_sprite);
    ObjectOnFieldPtr wall_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_WALL]);
    AllObjectsPtrs.emplace_back(wall_ptr);

    Water water;
    AllObjects.emplace_back(water);
    sf::Texture water_texture;
    AllTexturesOfSprites.emplace_back(water_texture);
    sf::Sprite water_sprite;
    AllSprites.emplace_back(water_sprite);
    ObjectOnFieldPtr water_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_WATER]);
    AllObjectsPtrs.emplace_back(water_ptr);

    Operator operator_is("Is");
    AllObjects.emplace_back(operator_is);
    sf::Texture operator_is_texture;
    AllTexturesOfSprites.emplace_back(operator_is_texture);
    sf::Sprite operator_is_sprite;
    AllSprites.emplace_back(operator_is_sprite);
    ObjectOnFieldPtr operator_is_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_IS]);
    AllObjectsPtrs.emplace_back(operator_is_ptr);

    Operator operator_and("And");
    AllObjects.emplace_back(operator_and);
    sf::Texture operator_and_texture;
    AllTexturesOfSprites.emplace_back(operator_and_texture);
    sf::Sprite operator_and_sprite;
    AllSprites.emplace_back(operator_and_sprite);
    ObjectOnFieldPtr operator_and_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_AND]);
    AllObjectsPtrs.emplace_back(operator_and_ptr);

    Noun babatext(AllObjectsPtrs[LOAD_BABA]);
    AllObjects.emplace_back(babatext);
    sf::Texture babatext_texture;
    AllTexturesOfSprites.emplace_back(babatext_texture);
    sf::Sprite babatext_sprite;
    AllSprites.emplace_back(babatext_sprite);
    ObjectOnFieldPtr babatext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_BABATEXT]);
    AllObjectsPtrs.emplace_back(babatext_ptr);

    Noun flagtext(AllObjectsPtrs[LOAD_FLAG]);
    AllObjects.emplace_back(flagtext);
    sf::Texture flagtext_texture;
    AllTexturesOfSprites.emplace_back(flagtext_texture);
    sf::Sprite flagtext_sprite;
    AllSprites.emplace_back(flagtext_sprite);
    ObjectOnFieldPtr flagtext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_FLAGTEXT]);
    AllObjectsPtrs.emplace_back(flagtext_ptr);

    Noun lavatext(AllObjectsPtrs[LOAD_LAVA]);
    AllObjects.emplace_back(lavatext);
    sf::Texture lavatext_texture;
    AllTexturesOfSprites.emplace_back(lavatext_texture);
    sf::Sprite lavatext_sprite;
    AllSprites.emplace_back(lavatext_sprite);
    ObjectOnFieldPtr lavatext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_LAVATEXT]);
    AllObjectsPtrs.emplace_back(lavatext_ptr);

    Noun rocktext(AllObjectsPtrs[LOAD_ROCK]);
    AllObjects.emplace_back(rocktext);
    sf::Texture rocktext_texture;
    AllTexturesOfSprites.emplace_back(rocktext_texture);
    sf::Sprite rocktext_sprite;
    AllSprites.emplace_back(rocktext_sprite);
    ObjectOnFieldPtr rocktext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_ROCKTEXT]);
    AllObjectsPtrs.emplace_back(rocktext_ptr);

    Noun skulltext(AllObjectsPtrs[LOAD_SKULL]);
    AllObjects.emplace_back(skulltext);
    sf::Texture skulltext_texture;
    AllTexturesOfSprites.emplace_back(skulltext_texture);
    sf::Sprite skulltext_sprite;
    AllSprites.emplace_back(skulltext_sprite);
    ObjectOnFieldPtr skulltext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_SKULLTEXT]);
    AllObjectsPtrs.emplace_back(skulltext_ptr);

    Noun treetext(AllObjectsPtrs[LOAD_TREE]);
    AllObjects.emplace_back(treetext);
    sf::Texture treetext_texture;
    AllTexturesOfSprites.emplace_back(treetext_texture);
    sf::Sprite treetext_sprite;
    AllSprites.emplace_back(treetext_sprite);
    ObjectOnFieldPtr treetext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_TREETEXT]);
    AllObjectsPtrs.emplace_back(treetext_ptr);

    Noun walltext(AllObjectsPtrs[LOAD_WALL]);
    AllObjects.emplace_back(walltext);
    sf::Texture walltext_texture;
    AllTexturesOfSprites.emplace_back(walltext_texture);
    sf::Sprite walltext_sprite;
    AllSprites.emplace_back(walltext_sprite);
    ObjectOnFieldPtr walltext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_WALLTEXT]);
    AllObjectsPtrs.emplace_back(walltext_ptr);

    Noun watertext(AllObjectsPtrs[LOAD_WATER]);
    AllObjects.emplace_back(watertext);
    sf::Texture watertext_texture;
    AllTexturesOfSprites.emplace_back(watertext_texture);
    sf::Sprite watertext_sprite;
    AllSprites.emplace_back(watertext_sprite);
    ObjectOnFieldPtr watertext_ptr = std::make_shared<ObjectOnField>(AllObjects[LOAD_WATERTEXT]);
    AllObjectsPtrs.emplace_back(watertext_ptr);






    for (int i=0; i < AllObjects.size(); i++)
    {
        AllTexturesOfSprites[i].loadFromFile(AllObjects[i].getImagePath());
        AllSprites[i].setTexture(AllTexturesOfSprites[i]);
        AllSprites[i].setScale(sf::Vector2f((64.0f/AllTexturesOfSprites[i].getSize().x),(64.0f/AllTexturesOfSprites[i].getSize().y)));
        AllObjectsPtrs[i]->SetSpritePtr(std::make_shared<sf::Sprite>(AllSprites[i]));
    }

}