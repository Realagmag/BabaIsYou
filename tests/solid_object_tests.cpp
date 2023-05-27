#include <catch2/catch.hpp>

#include "../src/SolidObject.h"
#include "../src/SolidObjects/Baba.h"
#include "../src/Parameters.h"

TEST_CASE("SolidObject tests", "[SolidObject]")
{
    ObjectOnFieldPtr solid_object = std::make_shared<SolidObject>();
    ObjectOnFieldPtr baba_ptr = std::make_shared<Baba>();

    SECTION("Getters")
    {
        CHECK(solid_object->getImagePath() == Parameters::PATHS.at("Empty"));
        CHECK(solid_object->getType() == "SolidObject");
    }

    SECTION("Set and clear temporary identity")
    {
        solid_object->setTemporaryIdentity(baba_ptr);
        CHECK(solid_object->getImagePath() == baba_ptr->getImagePath());
        CHECK(solid_object->getType() == "SolidObject");
        solid_object->clearTemporaryIdentity();
        CHECK(solid_object->getImagePath() == Parameters::PATHS.at("Empty"));
        CHECK(solid_object->getType() == "SolidObject");
        CHECK(solid_object->getTemporaryIdentity() == nullptr);
    }
}