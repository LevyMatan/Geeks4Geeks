/**
 * @file add_binary_strings.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <string>

/**
 * @brief Given two binary strings A and B consisting of only 0s and 1s.
 *        Find the resultant string after adding the two Binary Strings.
 *        Note: The input strings may contain leading zeros but the output
 *              string should not have any leading zeros.
 *
 *          Example 1:
 *
 *          Input:
 *          A = "1101", B = "111"
 *          Output: 10100
 *          Explanation:
 *           1101
 *          + 111
 *          10100
 *          Example 2:
 *
 *          Input:
 *          A = "10", B = "01"
 *          Output: 11
 *          Explanation:
 *            10
 *          + 01
 *            11
 *
 * URL: https://practice.geeksforgeeks.org/problems/add-binary-strings3805/1
 */
namespace add_binary_strings
{

    /**
     * @brief
     *
     * @param str
     * @param charToRemove
     */
    static void removeTrailingCharacters(std::string &str, const char charToRemove)
    {
        str.erase(str.find_last_not_of(charToRemove) + 1, std::string::npos);
    }

    /**
     * @brief
     *
     * @param sum
     * @param carry
     * @param digit
     */
    static void comput_carry_and_char_from_sum(int sum, int &carry, char &digit)
    {
        if (0 == sum)
        {
            carry = 0;
            digit = '0';
        }
        else if (1 == sum)
        {
            carry = 0;
            digit = '1';
        }
        else if (2 == sum)
        {
            carry = 1;
            digit = '0';
        }
        else if (3 == sum)
        {
            carry = 1;
            digit = '1';
        }
    }

    /**
     * @brief
     *
     * @param A
     * @param B
     * @return std::string
     */
    std::string add_binary(std::string A, std::string B)
    {
        std::reverse(A.begin(), A.end());
        std::reverse(B.begin(), B.end());
        unsigned long i;
        int carry = 0;
        std::string result("");
        for (i = 0; (i < A.size()) && (i < B.size()); i++)
        {
            int digit_A = A[i] - '0';
            int digit_B = B[i] - '0';
            // printf("%d\n", digit_A);
            int sum = carry + digit_A + digit_B;
            // cout << "sum = " << sum << endl;
            char digit = '0';
            comput_carry_and_char_from_sum(sum, carry, digit);
            result += digit;
        }
        // cout << result << endl;
        while (i < A.size())
        {
            int digit_A = A[i] - '0';
            int sum = carry + digit_A;
            char digit = '0';
            comput_carry_and_char_from_sum(sum, carry, digit);
            result += digit;
            i++;
        }
        while (i < B.size())
        {
            int digit_B = B[i] - '0';
            int sum = carry + digit_B;
            char digit = '0';
            comput_carry_and_char_from_sum(sum, carry, digit);
            result += digit;
            i++;
        }
        if (1 == carry)
        {
            result += '1';
        }

        // remove trailing zeros from string
        removeTrailingCharacters(result, '0');
        reverse(result.begin(), result.end());

        return result;
    }
}  // namespace add_binary_strings