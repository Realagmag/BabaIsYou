#pragma once

#include <iostream>
#include <map>

struct Parameters
{
    // Number of archival states to store
    static const int MAX_ARCHIVAL_STATES;

    // Paths to textures
    static const std::map<std::string, std::string> PATHS;
};
