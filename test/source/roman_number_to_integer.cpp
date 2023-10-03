/**
 * @file roman_number_to_integer.cpp
 * @brief
 * @version 0.1
 * @date 2023-10-03
 *
 *
 */
#include <doctest/doctest.h>
#include <roman_number_to_integer/roman_number_to_integer.h>

TEST_CASE("Roman Number to Integer: Toy Test")
{
    std::string roman_number = "X";
    CHECK(roman_to_decimal(roman_number) == 10);

    roman_number = "IX";
    CHECK(roman_to_decimal(roman_number) == 9);

    roman_number = "MCMXC";
    CHECK(roman_to_decimal(roman_number) == 1990);
}