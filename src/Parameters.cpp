#include "Parameters.h"

const unsigned int Parameters::MAX_ARCHIVAL_STATES = 30;

const unsigned int Parameters::NUMBER_OF_LEVELS = 8;

const std::map<std::string, std::string> Parameters::OBJECT_PATHS = {
    {"Empty", "../textures/Empty.png"},
    {"Baba", "../textures/Baba.png"},
    {"BabaUp", "../textures/BabaUp.png"},
    {"BabaDown", "../textures/BabaDown.png"},
    {"BabaLeft", "../textures/BabaLeft.png"},
    {"BabaRight", "../textures/BabaRight.png"},
    {"Flag", "../textures/Flag.png"},
    {"Rock", "../textures/Rock.png"},
    {"Wall", "../textures/Wall.png"},
    {"Water", "../textures/Water.png"},
    {"Lava", "../textures/Lava.png"},
    {"Skull", "../textures/Skull.png"},
    {"Tree", "../textures/Tree.png"},
    {"Grass", "../textures/Grass.png"},
    {"Is", "../textures/Is.png"},
    {"And", "../textures/And.png"},
    {"Babatext", "../textures/Babatext.png"},
    {"Defeattext", "../textures/Defeattext.png"},
    {"Flagtext", "../textures/Flagtext.png"},
    {"Floattext", "../textures/Floattext.png"},
    {"Hottext", "../textures/Hottext.png"},
    {"Melttext", "../textures/Melttext.png"},
    {"Pushtext", "../textures/Pushtext.png"},
    {"Rocktext", "../textures/Rocktext.png"},
    {"Sinktext", "../textures/Sinktext.png"},
    {"Skulltext", "../textures/Skulltext.png"},
    {"Stoptext", "../textures/Stoptext.png"},
    {"Treetext", "../textures/Treetext.png"},
    {"Walltext", "../textures/Walltext.png"},
    {"Watertext", "../textures/Watertext.png"},
    {"Wintext", "../textures/Wintext.png"},
    {"Youtext", "../textures/Youtext.png"},
    {"Lavatext", "../textures/Lavatext.png"},
};

const std::map<std::string, std::string> Parameters::FONT_PATHS = {
    {"ARIBLO", "../fonts/ARIBL0.ttf"}
};

const std::map<std::string, std::string> Parameters::AUDIO_PATHS = {
    {"Win", "../sounds/win.wav"},
    {"Lose", "../sounds/lose.wav"},
    {"Move", "../sounds/move.wav"},
    {"Menu", "../sounds/menumusic.ogg"},
    {"Level", "../sounds/levelmusic.ogg"}
};

const std::string Parameters::CHOOSE_LEVEL_TEXT_PATH = "../textures/choose_level.png";