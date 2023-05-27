#include <catch2/catch.hpp>

#include "../src/SolidObjects/Baba.h"
#include "../src/Parameters.h"

TEST_CASE("Baba tests", "[Baba]")
{
    Baba baba;

    SECTION("Getters")
    {
        CHECK(baba.getImagePath() == "../" + Parameters::PATHS.at("Baba"));
        CHECK(baba.getImagePath("up") == "../" + Parameters::PATHS.at("BabaUp"));
        CHECK(baba.getImagePath("down") == "../" + Parameters::PATHS.at("BabaDown"));
        CHECK(baba.getImagePath("left") == "../" + Parameters::PATHS.at("BabaLeft"));
        CHECK(baba.getImagePath("right") == "../" + Parameters::PATHS.at("BabaRight"));
    }
}