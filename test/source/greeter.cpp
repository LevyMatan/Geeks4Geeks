#include <doctest/doctest.h>
#include <geeks4geeks/version.h>
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

// TEST_CASE("Greeter version")
// {
//     CHECK(std::string(GEEKS4GEEKS_VERSION) == std::string("v0.9.2"));
//     static_assert(std::string_view(GEEKS4GEEKS_VERSION) == std::string_view("v0.9.2"));
// }
