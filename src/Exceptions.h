#pragma once

#include <stdexcept>
#include <string>
#include <iostream>

class InvalidPropertyException : public std::invalid_argument
{
public:
    InvalidPropertyException(const std::string &property);
};

class IndexOutOfBoardSizeException : public std::out_of_range
{
    public:
        IndexOutOfBoardSizeException(const std::string &dimension);
};

class InvalidDirectionException : public std::invalid_argument
{
    public:
        InvalidDirectionException(const std::string &direction);
};

class InvalidPathException : public std::invalid_argument
{
    public:
        InvalidPathException(const std::string &path);
};