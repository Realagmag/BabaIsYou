#include "Game.h"
#include <fstream>
#include <sstream>
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
    setCurrentLevel(0);
    CreateObjectInstances();
    LoadLevelsFromFile();
    SetupBoard();
}

Game::~Game(){}

void Game::HandleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && IsKeyReleased)
    {
        IsKeyReleased = false;
        if (GameHasStarted){
        Action action = UP;
        _board.updateState(action);}
        else
        {}
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && IsKeyReleased)
    {
        IsKeyReleased = false;
        if (GameHasStarted){
        Action action = LEFT;
        _board.updateState(action);}
        else{
            if (_current_level > 0) _current_level -= 1;}
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && IsKeyReleased)
    {
        IsKeyReleased = false;
        if (GameHasStarted){
        Action action = DOWN;
        _board.updateState(action);}
        else
        {}
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && IsKeyReleased)
    {
        IsKeyReleased = false;
        if (GameHasStarted){
        Action action = RIGHT;
        _board.updateState(action);}
        else{
            if (_current_level < LoadedLevels.size()-1) _current_level += 1;}
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && IsKeyReleased)
    {
        IsKeyReleased = false;
        if (GameHasStarted){
        Board new_board(_board.getXSize(), _board.getYSize());
        _board = new_board;
        SetupBoard();}
        else
        {}
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && IsKeyReleased)
    {
        IsKeyReleased = false;
        if (GameHasStarted){}
        else {
            GameHasStarted = true;
            Board new_board(_board.getXSize(), _board.getYSize());
            _board = new_board;
            SetupBoard();}

    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
    !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        IsKeyReleased = true;
    }
}

void Game::Update()
{
    _window.Update(GameHasStarted); // Update window events.
}

void Game::Render()
{
    _window.BeginDraw(); // Clear.
    if (GameHasStarted){
    _window.DrawBoard(_board);}
    else{
    _window.DrawMenu(_current_level);}
    _window.EndDraw(); // Display.
}

Window* Game::GetWindow()
{
    return &_window;
}

int Game::getCurrentLevel()
{
    return _current_level;
}

void Game::setCurrentLevel(int level_number)
{
    _current_level = level_number;
}

void Game::SetupBoard()
{
    for (int i = 0; i < _board.getXSize(); i++)
    {
        for (int j = 0; j< _board.getYSize(); j++)
        {
            std::string letter = LoadedLevels[getCurrentLevel()][j][i];
            if (letter == "-"){}
            else if (letter == "and") _board.addObject(i,j,AllObjectsPtrs[LOAD_AND]);
            else if (letter == "B") _board.addObject(i,j,AllObjectsPtrs[LOAD_BABA]);
            else if (letter == "b") _board.addObject(i,j,AllObjectsPtrs[LOAD_BABATEXT]);
            else if (letter == "defeat") _board.addObject(i,j,AllObjectsPtrs[LOAD_DEFEATTEXT]);
            else if (letter == "F") _board.addObject(i,j,AllObjectsPtrs[LOAD_FLAG]);
            else if (letter == "f") _board.addObject(i,j,AllObjectsPtrs[LOAD_FLAGTEXT]);
            else if (letter == "float") _board.addObject(i,j,AllObjectsPtrs[LOAD_FLOATTEXT]);
            else if (letter == "hot") _board.addObject(i,j,AllObjectsPtrs[LOAD_HOTTEXT]);
            else if (letter == "is") _board.addObject(i,j,AllObjectsPtrs[LOAD_IS]);
            else if (letter == "L") _board.addObject(i,j,AllObjectsPtrs[LOAD_LAVA]);
            else if (letter == "l") _board.addObject(i,j,AllObjectsPtrs[LOAD_LAVATEXT]);
            else if (letter == "melt") _board.addObject(i,j,AllObjectsPtrs[LOAD_MELTTEXT]);
            else if (letter == "push") _board.addObject(i,j,AllObjectsPtrs[LOAD_PUSHTEXT]);
            else if (letter == "R") _board.addObject(i,j,AllObjectsPtrs[LOAD_ROCK]);
            else if (letter == "r") _board.addObject(i,j,AllObjectsPtrs[LOAD_ROCKTEXT]);
            else if (letter == "sink") _board.addObject(i,j,AllObjectsPtrs[LOAD_SINKTEXT]);
            else if (letter == "S") _board.addObject(i,j,AllObjectsPtrs[LOAD_SKULL]);
            else if (letter == "s") _board.addObject(i,j,AllObjectsPtrs[LOAD_SKULLTEXT]);
            else if (letter == "stop") _board.addObject(i,j,AllObjectsPtrs[LOAD_STOPTEXT]);
            else if (letter == "T") _board.addObject(i,j,AllObjectsPtrs[LOAD_TREE]);
            else if (letter == "t") _board.addObject(i,j,AllObjectsPtrs[LOAD_TREETEXT]);
            else if (letter == "W") _board.addObject(i,j,AllObjectsPtrs[LOAD_WALL]);
            else if (letter == "w") _board.addObject(i,j,AllObjectsPtrs[LOAD_WALLTEXT]);
            else if (letter == "WATER") _board.addObject(i,j,AllObjectsPtrs[LOAD_WATER]);
            else if (letter == "water") _board.addObject(i,j,AllObjectsPtrs[LOAD_WATERTEXT]);
            else if (letter == "win") _board.addObject(i,j,AllObjectsPtrs[LOAD_WINTEXT]);
            else if (letter == "you") _board.addObject(i,j,AllObjectsPtrs[LOAD_YOUTEXT]);
        }
    }
    _board.updateRules();
}

void Game::LoadLevelsFromFile()
{
    std::fstream file;
    file.open("../src/levels.txt", std::ios::in);
    if (file.is_open())
    {
        while(file.eof()==false)
        {
            std::vector<std::vector<std::string>> rows;
            std::vector<std::string> row_of_letters;
            std::string num_of_level;
            std::string row;
            std::string object_letter;
            getline(file, num_of_level);
            for (int i = 0; i < 16; i++)
            {
                getline(file, row);
                std::stringstream ss1(row);
                while(getline(ss1, object_letter, ','))
                {
                    object_letter.erase(std::remove_if(object_letter.begin(), object_letter.end(), ::isspace), object_letter.end());
                    row_of_letters.push_back(object_letter);
                }
                rows.push_back(row_of_letters);
                row_of_letters.clear();
                ss1.clear();
            }
            LoadedLevels.push_back(rows);
        }
        file.close();
    }
}

void Game::CreateObjectInstances()
{
    // Creates Textures, Sprites and ObjectOnField instances and stores it
    sf::Texture baba_texture;
    AllTexturesOfSprites.emplace_back(baba_texture);
    sf::Sprite baba_sprite;
    AllSprites.emplace_back(baba_sprite);
    ObjectOnFieldPtr baba_ptr = std::make_shared<Baba>();
    AllObjectsPtrs.emplace_back(baba_ptr);

    sf::Texture flag_texture;
    AllTexturesOfSprites.emplace_back(flag_texture);
    sf::Sprite flag_sprite;
    AllSprites.emplace_back(flag_sprite);
    ObjectOnFieldPtr flag_ptr = std::make_shared<Flag>();
    AllObjectsPtrs.emplace_back(flag_ptr);

    sf::Texture lava_texture;
    AllTexturesOfSprites.emplace_back(lava_texture);
    sf::Sprite lava_sprite;
    AllSprites.emplace_back(lava_sprite);
    ObjectOnFieldPtr lava_ptr = std::make_shared<Lava>();
    AllObjectsPtrs.emplace_back(lava_ptr);

    sf::Texture rock_texture;
    AllTexturesOfSprites.emplace_back(rock_texture);
    sf::Sprite rock_sprite;
    AllSprites.emplace_back(rock_sprite);
    ObjectOnFieldPtr rock_ptr = std::make_shared<Rock>();
    AllObjectsPtrs.emplace_back(rock_ptr);

    sf::Texture skull_texture;
    AllTexturesOfSprites.emplace_back(skull_texture);
    sf::Sprite skull_sprite;
    AllSprites.emplace_back(skull_sprite);
    ObjectOnFieldPtr skull_ptr = std::make_shared<Skull>();
    AllObjectsPtrs.emplace_back(skull_ptr);

    sf::Texture tree_texture;
    AllTexturesOfSprites.emplace_back(tree_texture);
    sf::Sprite tree_sprite;
    AllSprites.emplace_back(tree_sprite);
    ObjectOnFieldPtr tree_ptr = std::make_shared<Tree>();
    AllObjectsPtrs.emplace_back(tree_ptr);

    sf::Texture wall_texture;
    AllTexturesOfSprites.emplace_back(wall_texture);
    sf::Sprite wall_sprite;
    AllSprites.emplace_back(wall_sprite);
    ObjectOnFieldPtr wall_ptr = std::make_shared<Wall>();
    AllObjectsPtrs.emplace_back(wall_ptr);

    sf::Texture water_texture;
    AllTexturesOfSprites.emplace_back(water_texture);
    sf::Sprite water_sprite;
    AllSprites.emplace_back(water_sprite);
    ObjectOnFieldPtr water_ptr = std::make_shared<Water>();
    AllObjectsPtrs.emplace_back(water_ptr);

    sf::Texture operator_is_texture;
    AllTexturesOfSprites.emplace_back(operator_is_texture);
    sf::Sprite operator_is_sprite;
    AllSprites.emplace_back(operator_is_sprite);
    ObjectOnFieldPtr operator_is_ptr = std::make_shared<Operator>("Is");
    AllObjectsPtrs.emplace_back(operator_is_ptr);

    sf::Texture operator_and_texture;
    AllTexturesOfSprites.emplace_back(operator_and_texture);
    sf::Sprite operator_and_sprite;
    AllSprites.emplace_back(operator_and_sprite);
    ObjectOnFieldPtr operator_and_ptr = std::make_shared<Operator>("And");
    AllObjectsPtrs.emplace_back(operator_and_ptr);

    sf::Texture babatext_texture;
    AllTexturesOfSprites.emplace_back(babatext_texture);
    sf::Sprite babatext_sprite;
    AllSprites.emplace_back(babatext_sprite);
    ObjectOnFieldPtr babatext_ptr = std::make_shared<Noun>(baba_ptr);
    AllObjectsPtrs.emplace_back(babatext_ptr);

    sf::Texture flagtext_texture;
    AllTexturesOfSprites.emplace_back(flagtext_texture);
    sf::Sprite flagtext_sprite;
    AllSprites.emplace_back(flagtext_sprite);
    ObjectOnFieldPtr flagtext_ptr = std::make_shared<Noun>(flag_ptr);
    AllObjectsPtrs.emplace_back(flagtext_ptr);

    sf::Texture lavatext_texture;
    AllTexturesOfSprites.emplace_back(lavatext_texture);
    sf::Sprite lavatext_sprite;
    AllSprites.emplace_back(lavatext_sprite);
    ObjectOnFieldPtr lavatext_ptr = std::make_shared<Noun>(lava_ptr);
    AllObjectsPtrs.emplace_back(lavatext_ptr);

    sf::Texture rocktext_texture;
    AllTexturesOfSprites.emplace_back(rocktext_texture);
    sf::Sprite rocktext_sprite;
    AllSprites.emplace_back(rocktext_sprite);
    ObjectOnFieldPtr rocktext_ptr = std::make_shared<Noun>(rock_ptr);
    AllObjectsPtrs.emplace_back(rocktext_ptr);

    sf::Texture skulltext_texture;
    AllTexturesOfSprites.emplace_back(skulltext_texture);
    sf::Sprite skulltext_sprite;
    AllSprites.emplace_back(skulltext_sprite);
    ObjectOnFieldPtr skulltext_ptr = std::make_shared<Noun>(skull_ptr);
    AllObjectsPtrs.emplace_back(skulltext_ptr);

    sf::Texture treetext_texture;
    AllTexturesOfSprites.emplace_back(treetext_texture);
    sf::Sprite treetext_sprite;
    AllSprites.emplace_back(treetext_sprite);
    ObjectOnFieldPtr treetext_ptr = std::make_shared<Noun>(tree_ptr);
    AllObjectsPtrs.emplace_back(treetext_ptr);

    sf::Texture walltext_texture;
    AllTexturesOfSprites.emplace_back(walltext_texture);
    sf::Sprite walltext_sprite;
    AllSprites.emplace_back(walltext_sprite);
    ObjectOnFieldPtr walltext_ptr = std::make_shared<Noun>(wall_ptr);
    AllObjectsPtrs.emplace_back(walltext_ptr);

    sf::Texture watertext_texture;
    AllTexturesOfSprites.emplace_back(watertext_texture);
    sf::Sprite watertext_sprite;
    AllSprites.emplace_back(watertext_sprite);
    ObjectOnFieldPtr watertext_ptr = std::make_shared<Noun>(water_ptr);
    AllObjectsPtrs.emplace_back(watertext_ptr);

    sf::Texture defeattext_texture;
    AllTexturesOfSprites.emplace_back(defeattext_texture);
    sf::Sprite defeattext_sprite;
    AllSprites.emplace_back(defeattext_sprite);
    ObjectOnFieldPtr defeattext_ptr = std::make_shared<Property>("Defeat");
    AllObjectsPtrs.emplace_back(defeattext_ptr);

    sf::Texture floattext_texture;
    AllTexturesOfSprites.emplace_back(floattext_texture);
    sf::Sprite floattext_sprite;
    AllSprites.emplace_back(floattext_sprite);
    ObjectOnFieldPtr floattext_ptr = std::make_shared<Property>("Float");
    AllObjectsPtrs.emplace_back(floattext_ptr);

    sf::Texture hottext_texture;
    AllTexturesOfSprites.emplace_back(hottext_texture);
    sf::Sprite hottext_sprite;
    AllSprites.emplace_back(hottext_sprite);
    ObjectOnFieldPtr hottext_ptr = std::make_shared<Property>("Hot");
    AllObjectsPtrs.emplace_back(hottext_ptr);

    sf::Texture melttext_texture;
    AllTexturesOfSprites.emplace_back(melttext_texture);
    sf::Sprite melttext_sprite;
    AllSprites.emplace_back(melttext_sprite);
    ObjectOnFieldPtr melttext_ptr = std::make_shared<Property>("Melt");
    AllObjectsPtrs.emplace_back(melttext_ptr);

    sf::Texture pushtext_texture;
    AllTexturesOfSprites.emplace_back(pushtext_texture);
    sf::Sprite pushtext_sprite;
    AllSprites.emplace_back(pushtext_sprite);
    ObjectOnFieldPtr pushtext_ptr = std::make_shared<Property>("Push");
    AllObjectsPtrs.emplace_back(pushtext_ptr);

    sf::Texture sinktext_texture;
    AllTexturesOfSprites.emplace_back(sinktext_texture);
    sf::Sprite sinktext_sprite;
    AllSprites.emplace_back(sinktext_sprite);
    ObjectOnFieldPtr sinktext_ptr = std::make_shared<Property>("Sink");
    AllObjectsPtrs.emplace_back(sinktext_ptr);

    sf::Texture stoptext_texture;
    AllTexturesOfSprites.emplace_back(stoptext_texture);
    sf::Sprite stoptext_sprite;
    AllSprites.emplace_back(stoptext_sprite);
    ObjectOnFieldPtr stoptext_ptr = std::make_shared<Property>("Stop");
    AllObjectsPtrs.emplace_back(stoptext_ptr);

    sf::Texture wintext_texture;
    AllTexturesOfSprites.emplace_back(wintext_texture);
    sf::Sprite wintext_sprite;
    AllSprites.emplace_back(wintext_sprite);
    ObjectOnFieldPtr wintext_ptr = std::make_shared<Property>("Win");
    AllObjectsPtrs.emplace_back(wintext_ptr);

    sf::Texture youtext_texture;
    AllTexturesOfSprites.emplace_back(youtext_texture);
    sf::Sprite youtext_sprite;
    AllSprites.emplace_back(youtext_sprite);
    ObjectOnFieldPtr youtext_ptr = std::make_shared<Property>("You");
    AllObjectsPtrs.emplace_back(youtext_ptr);

    for (int i=0; i < AllObjectsPtrs.size(); i++)
    {
        AllTexturesOfSprites[i].loadFromFile(AllObjectsPtrs[i]->getImagePath());
        AllSprites[i].setTexture(AllTexturesOfSprites[i]);
        AllSprites[i].setScale(sf::Vector2f((64.0f/AllTexturesOfSprites[i].getSize().x),(64.0f/AllTexturesOfSprites[i].getSize().y)));
        AllObjectsPtrs[i]->SetSpritePtr(std::make_shared<sf::Sprite>(AllSprites[i]));
    }

}