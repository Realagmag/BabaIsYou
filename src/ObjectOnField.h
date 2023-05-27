#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Parameters.h"

class ObjectOnField
{
protected:
    std::string _imagePath;
    std::string _type;

    /* Cointains texture and size !SFML! */
    std::shared_ptr<sf::Sprite> _spritePtr;

    /** Properties of the object. */
    std::map<std::string, bool> _properties = {
        {"You", false},
        {"Win", false},
        {"Stop", false},
        {"Push", false},
        {"Sink", false},
        {"Defeat", false},
        {"Hot", false},
        {"Melt", false},
        {"Float", false}};

public:
    ObjectOnField(std::string imagePath);
    ObjectOnField();
    virtual ~ObjectOnField();

    // SFML part
    virtual void SetSpritePtr(std::shared_ptr<sf::Sprite> newSpritePtr);
    virtual std::shared_ptr<sf::Sprite> GetSpritePtr() const;

    virtual std::string getImagePath() const;

    virtual std::string getType() const;

    virtual std::shared_ptr<ObjectOnField> getTemporaryIdentity() const;

    virtual void setTemporaryIdentity(const std::shared_ptr<ObjectOnField> &objectPtr);

    virtual void clearTemporaryIdentity();

    virtual std::shared_ptr<ObjectOnField> getSolidObjectPtr() const;

    /** Sets all properties to false. */
    void resetProperties();

    virtual bool getProperty(const std::string &property) const;

    virtual void setProperty(const std::string &property, bool value);

    virtual std::string getNounImagePath() const;

    virtual std::string getText() const;
};

using ObjectOnFieldPtr = std::shared_ptr<ObjectOnField>;
using ObjectOnFieldPtrs2Vector = std::vector<std::vector<ObjectOnFieldPtr>>;
using ObjectOnFieldPtrs3Vector = std::vector<std::vector<std::vector<ObjectOnFieldPtr>>>;