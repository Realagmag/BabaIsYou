#pragma once

#include <iostream>
#include <map>

struct Parameters
{
    // Number of archival states to store
    static const unsigned int MAX_ARCHIVAL_STATES;

    // Number of levels in the game, now max 8
    static const unsigned int NUMBER_OF_LEVELS;

    // Paths to textures
    static const std::map<std::string, std::string> OBJECT_PATHS;

    // Paths to fonts
    static const std::map<std::string, std::string> FONT_PATHS;

    // Paths to audio
    static const std::map<std::string, std::string> AUDIO_PATHS;

    static const std::string CHOOSE_LEVEL_TEXT_PATH;
};
