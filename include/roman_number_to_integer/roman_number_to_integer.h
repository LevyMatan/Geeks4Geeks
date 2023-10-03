#pragma once
/**
 * @file roman_number_to_integer.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief Header file for roman_number_to_integer.c
 * @version 0.1
 * @date 2023-10-03
 *
 *
 */
#include <string>

/**
 * @brief Given a string of roman numeral, convert it to an integer.
 *
 * @param str Roman number as string, 1<=roman no range<=3999
 * @return int
 */
int roman_to_decimal(std::string &str);
