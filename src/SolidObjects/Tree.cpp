#include "Tree.h"
#include "../paths.h"

Tree::Tree(std::string imagePath) : SolidObject(imagePath)
{}

Tree::Tree()
{
    _imagePath = "../" + paths.at("Tree");
    _nounImagePath = "../" + paths.at("Treetext");
}