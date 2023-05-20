#pragma once

#include <iostream>
#include "paths.h"
#include <SFML/Graphics.hpp>
#include <memory>

class ObjectOnField
{
protected:
    std::string _imagePath;
    std::string _type;

    /* Cointains texture and size !SFML! */
    std::shared_ptr<sf::Sprite> _sprite_ptr;

public:

    ObjectOnField(std::string imagePath);
    ObjectOnField();
    virtual ~ObjectOnField();

    // SFML part
    void SetSpritePtr(std::shared_ptr<sf::Sprite> new_sprite_ptr);
    std::shared_ptr<sf::Sprite> GetSpritePtr();

    virtual std::string getImagePath() const;

    virtual std::string getType() const;

    virtual std::shared_ptr<ObjectOnField> getTemporaryIdentity() const;

    virtual void setTemporaryIdentity(const std::shared_ptr<ObjectOnField> &objectPtr);

    virtual void clearTemporaryIdentity();

    bool isYou = false;
    bool isWin = false;
    bool isStop = false;
    bool isPush = false;
    bool isSink = false;
    bool isDefeat = false;
    bool isHot = false;
    bool isMelt = false;
};

using ObjectOnFieldPtr = std::shared_ptr<ObjectOnField>;
using ObjectOnFieldPtrs2Vector = std::vector<std::vector<ObjectOnFieldPtr>>;
using ObjectOnFieldPtrs3Vector = std::vector<std::vector<std::vector<ObjectOnFieldPtr>>>;