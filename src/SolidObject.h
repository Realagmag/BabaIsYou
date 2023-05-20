#pragma once

#include <iostream>
#include <string>

#include "ObjectOnField.h"

class SolidObject : public ObjectOnField
{
private:
    /** Ptr to the object which is temporary identity.
     * If it is nullptr, then the object does not have temporary identity.
     * This is when SOLID_OBJECT IS ANOTHER_SOLID_OBJECT. */
    ObjectOnFieldPtr _temporaryIdentity = nullptr;

    std::string _temporaryImagePath = "";
    std::string _temporaryType = "";

public:
    SolidObject(std::string imagePath);
    SolidObject();

    std::string getImagePath() const override;

    std::string getType() const override;

    ObjectOnFieldPtr getTemporaryIdentity() const override;

    void setTemporaryIdentity(const ObjectOnFieldPtr &objectPtr) override;

    void clearTemporaryIdentity() override;
};