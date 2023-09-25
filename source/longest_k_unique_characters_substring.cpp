/**
 * @file longest_k_unique_characters_substring.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-29
 *
 *
 */
#include <longest_k_unique_characters_substring/longest_k_unique_characters_substring.h>

#include <algorithm>
#include <climits>
/**
 * @brief find the length of the longest substring with k unique characters in a given string
 *        Algorithm:
 *        1. Create an array of size 26 (for each letter in the alphabet).
 *           The value in each cell will be the highest index of that char.
 *        2. Create a variable called start, which will be the start of the substring.
 *           It should be initialized to 0.
 *        3. iterate over the string, and for each char:
 *          3.1. Check if this character is already in our substring by looking at the value in the
 *               array.
 *          3.2. update the value in the array of the current char to be the current index.
 *
 *
 *
 * @param s string of only lower case characters
 * @param k number of unique characters
 * @return int the length of the longest substring with k unique characters in a given string, if
 * doesnt exist return -1
 */
int longest_k_substr(std::string s, int k)
{
#define MAX_CHARS 26
#define NOT_FOUND -1
    int start = 0;
    int char_index[MAX_CHARS];
    // Initilize array with -1
    for (int i = 0; i < MAX_CHARS; i++)
    {
        char_index[i] = NOT_FOUND;
    }
    int max_length = -1;
    int unique_chars = 0;

    for (std::string::size_type i = 0; i < s.size(); i++)
    {
        const char c = s[i];
        const int c_idx = c - 'a';

        if (NOT_FOUND == char_index[c_idx])
        {
            // If this char is new to our substring, increment unique_chars.
            unique_chars++;

            // If we have exactly k unique chars, our current substring is valid.
            if (unique_chars == k)
            {
                max_length = std::max(max_length, static_cast<int>(i - start + 1));
            }
            else if (unique_chars > k)
            {
                // If we have more than k unique chars, we need to remove chars from the start of
                // the substring We would like to remove the char which its last occurence is the
                // first in the substring. Need to find the index of the char to remove. Find the
                // index by finding the min value in char_index, except for -1.
                int min_index = INT_MAX;
                for (int j = 0; j < MAX_CHARS; j++)
                {
                    if (char_index[j] != NOT_FOUND)
                    {
                        min_index = std::min(min_index, char_index[j]);
                    }
                }
                // update start to be the index after the index of the char to remove.
                start = min_index + 1;

                // Update unique_chars.
                unique_chars--;

                // Remove the char from the array.
                char_index[s[min_index] - 'a'] = NOT_FOUND;
            }
        }
        else
        {
            if (unique_chars == k)
            {
                max_length = std::max(max_length, static_cast<int>(i - start + 1));
            }
        }

        // Update the last index of c.
        char_index[c_idx] = (int)i;
    }

    return max_length;
}