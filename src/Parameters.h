#pragma once

#include <iostream>
#include <map>

struct Parameters
{
    // Number of archival states to store
    static const unsigned int MAX_ARCHIVAL_STATES;

    // Number of levels in the game
    static const unsigned int NUMBER_OF_LEVELS;

    // Paths to textures
    static const std::map<std::string, std::string> PATHS;
};
