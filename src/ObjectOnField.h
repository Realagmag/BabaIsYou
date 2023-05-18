#pragma once

#include <iostream>
#include "paths.h"
#include <SFML/Graphics.hpp>
#include <memory>


class ObjectOnField
{
protected:
    std::string _imagePath;
    sf::Sprite sprite; //Cointains texture and size


public:

    ObjectOnField(std::string imagePath);
    ObjectOnField();
    virtual ~ObjectOnField();

    void SetTexture(sf::Texture texture); //SFML part
    std::shared_ptr<sf::Sprite> GetSpritePtr();

    virtual std::string getImagePath() const;
    virtual void setImagePath(std::string imagePath);

    bool isSolidObject = false;
    bool isObjectWord = false;
    bool isOperator = false;
    bool isKeyword = false;

    bool isYou = false;
    bool isWin = false;
    bool isStop = false;
    bool isPush = false;
    bool isSink = false;
    bool isDefeat = false;
    bool isHot = false;
    bool isMelt = false;
};