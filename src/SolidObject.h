#pragma once

#include <iostream>
#include <string>

#include "ObjectOnField.h"

class SolidObject : public ObjectOnField
{
protected:
    /** Ptr to the object which is temporary identity.
     * If it is nullptr, then the object does not have temporary identity.
     * This is when SOLID_OBJECT IS ANOTHER_SOLID_OBJECT. */
    ObjectOnFieldPtr _temporaryIdentity = nullptr;

    /** Image path of Noun which depends on this Solid Object. */
    std::string _nounImagePath;

public:
    SolidObject(std::string imagePath);
    SolidObject();

    std::shared_ptr<sf::Sprite> GetSpritePtr() const override;

    std::string getImagePath() const override;

    std::string getType() const override;

    ObjectOnFieldPtr getTemporaryIdentity() const override;

    void setTemporaryIdentity(const ObjectOnFieldPtr &objectPtr) override;

    void clearTemporaryIdentity() override;

    bool getProperty(const std::string &property) const override;

    std::string getNounImagePath() const override;

    // void setProperty(const std::string &property, bool value) override;
};