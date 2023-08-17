#pragma once
/**
 * @file next_smallest_palindrome.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief What is the next smallest palindrome?
 *        First, what is a palindrome? A palindrome is a word, number, phrase, or other sequence of
 * characters which reads the same backward as forward, such as madam, racecar. There are also
 * numeric palindromes, including date/time stamps using short digits 11/11/11 11:11 and long digits
 * 02/02/2020. Sentence-length palindromes ignore capitalization, punctuation, and word boundaries.
 * @version 0.1
 * @date 2023-08-17
 *
 *
 */

#include <vector>

using std::vector;
/**
 * @brief find the next smallest palindrome of n
 * Given a number, in the form of an array Num[] of size N containing digits from 1 to 9(inclusive).
 * The task is to find the next smallest palindrome strictly larger than the given number.
 */
vector<int> generateNextPalindrome(int num[], int n);