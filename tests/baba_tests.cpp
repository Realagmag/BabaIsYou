#include <catch2/catch.hpp>

#include "../src/SolidObjects/Baba.h"
#include "../src/Parameters.h"

TEST_CASE("Baba tests", "[Baba]")
{
    Baba baba;

    SECTION("Getters")
    {
        CHECK(baba.getImagePath() == "../" + Parameters::OBJECT_PATHS.at("Baba"));
        CHECK(baba.getImagePath("up") == "../" + Parameters::OBJECT_PATHS.at("BabaUp"));
        CHECK(baba.getImagePath("down") == "../" + Parameters::OBJECT_PATHS.at("BabaDown"));
        CHECK(baba.getImagePath("left") == "../" + Parameters::OBJECT_PATHS.at("BabaLeft"));
        CHECK(baba.getImagePath("right") == "../" + Parameters::OBJECT_PATHS.at("BabaRight"));
    }
}