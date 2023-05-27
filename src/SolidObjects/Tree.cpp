#include "Tree.h"
#include "../Parameters.h"

Tree::Tree(std::string imagePath) : SolidObject(imagePath)
{}

Tree::Tree()
{
    _imagePath = "../" + Parameters::PATHS.at("Tree");
    _nounImagePath = "../" + Parameters::PATHS.at("Treetext");
}