/**
 * @file next_smallest_palindrome.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-17
 *
 *
 */
#include <next_smallest_palindrome/next_smallest_palindrome.h>

/**
 * @brief find the next smallest palindrome of n
 * Given a number, in the form of an array Num[] of size N containing digits from 1 to 9(inclusive).
 * The task is to find the next smallest palindrome strictly larger than the given number.
 */
vector<int> generateNextPalindrome(int num[], int n)
{
    // find the index of the middle element
    int mid = n / 2;
    // A bool variable to check if copy of left side to right is sufficient or not
    bool leftsmaller = false;
    // end of left side is always 'mid -1'
    int i = mid - 1;
    // Beginning of right side depends if n is odd or even
    int j = (n % 2) ? mid + 1 : mid;
    // Initially, ignore the middle same digits
    while (i >= 0 && num[i] == num[j])
    {
        i--;
        j++;
    }
    // Find if the middle digit(s) need to be incremented or not (or copying left
    // side is not sufficient)
    if (i < 0 || num[i] < num[j])
    {
        leftsmaller = true;
    }
    // Copy the mirror of left to tight
    while (i >= 0)
    {
        num[j++] = num[i--];
    }
    // Handle the case where middle digit(s) must be incremented. This part of code is for CASE 1
    // and CASE 2.2
    if (leftsmaller)
    {
        int carry = 1;
        // If there are odd digits, then increment
        // the middle digit and store the carry
        if (n % 2 == 1)
        {
            num[mid] += carry;
            carry = num[mid] / 10;
            num[mid] %= 10;
        }
        i = mid - 1;
        j = (n % 2) ? mid + 1 : mid;
        // Add 1 to the rightmost digit of the left side, propagate the carry
        // towards MSB digit and simultaneously copying mirror of the left side
        // to the right side.
        while (i >= 0)
        {
            num[i] += carry;
            carry = num[i] / 10;
            num[i] %= 10;
            num[j++] = num[i--];  // copy mirror to right
        }
    }
    return vector<int>(num, num + n);
}