#include "Exceptions.h"

InvalidPropertyException::InvalidPropertyException(const std::string &property) :
    std::invalid_argument("Property " + property + " does not exist!") {}

IndexOutOfBoardSizeException::IndexOutOfBoardSizeException(const std::string &dimension) :
    std::out_of_range(dimension + " is out of board size!") {}

InvalidDirectionException::InvalidDirectionException(const std::string &direction) :
    std::invalid_argument("Direction " + direction + " does not exist!") {}

InvalidPathException::InvalidPathException(const std::string &path) :
    std::invalid_argument("Unable to load " + path) {}