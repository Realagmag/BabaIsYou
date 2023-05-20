#include <catch2/catch.hpp>

#include "../src/SolidObjects/Baba.h"
#include "../src/paths.h"

TEST_CASE("Baba tests", "[Baba]")
{
    Baba baba;

    SECTION("Getters")
    {
        CHECK(baba.getImagePath() == "../" + paths.at("Baba"));
        CHECK(baba.getImagePath("up") == "../" + paths.at("BabaUp"));
        CHECK(baba.getImagePath("down") == "../" + paths.at("BabaDown"));
        CHECK(baba.getImagePath("left") == "../" + paths.at("BabaLeft"));
        CHECK(baba.getImagePath("right") == "../" + paths.at("BabaRight"));
    }
}