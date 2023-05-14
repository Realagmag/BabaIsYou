#include <catch2/catch.hpp>

#include "../src/SolidObject.h"
#include "../src/SolidObjects/Baba.h"
#include "../src/paths.h"

TEST_CASE("SolidObject tests", "[SolidObject]")
{
    SolidObject solid_object;
    Baba baba;

    SECTION("Getters")
    {
        CHECK(solid_object.getImagePath() == paths.at("Empty"));
    }

    SECTION("Set and remove image path")
    {
        solid_object.setImagePath("newSolidObject.png");
        CHECK(solid_object.getImagePath() == "newSolidObject.png");
        solid_object.clearTemporaryImagePath();
        CHECK(solid_object.getImagePath() == paths.at("Empty"));
    }
}