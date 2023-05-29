#include "Tree.h"
#include "../Parameters.h"

Tree::Tree(std::string imagePath) : SolidObject(imagePath)
{}

Tree::Tree()
{
    _imagePath = Parameters::OBJECT_PATHS.at("Tree");
    _nounImagePath = Parameters::OBJECT_PATHS.at("Treetext");
}