#include <catch2/catch.hpp>

#include "../src/Noun.h"
#include "../src/SolidObjects/Baba.h"
#include "../src/Parameters.h"

TEST_CASE("Noun tests", "[Noun]")
{
    ObjectOnFieldPtr baba_ptr = std::make_shared<Baba>();
    ObjectOnFieldPtr noun = std::make_shared<Noun>(baba_ptr);

    SECTION("Getters")
    {
        CHECK(noun->getImagePath() == "../" + Parameters::PATHS.at("Babatext"));
        CHECK(noun->getType() == "Noun");
        CHECK(noun->getProperty("Push") == true);
        CHECK(noun->getProperty("Stop") == true);
        CHECK(noun->getSolidObjectPtr() == baba_ptr);
    }
}