#include <doctest/doctest.h>
#include <greeter/greeter.h>

#include <string>

TEST_CASE("Greeter")
{
    using namespace greeter;

    Greeter greeter("Tests");

    MESSAGE("This a little more info on the test");
    CHECK(greeter.greet(LanguageCode::EN) == "Hello, Tests!");
    CHECK(greeter.greet(LanguageCode::DE) == "Hallo Tests!");
    CHECK(greeter.greet(LanguageCode::ES) == "¡Hola Tests!");
    CHECK(greeter.greet(LanguageCode::FR) == "Bonjour Tests!");
    CHECK(greeter.greet(LanguageCode::HEB) == "Shalom Tests!");
}
