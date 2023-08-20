/**
* @file number_of_occurrences.cpp
* @author Matan Levy (levymatanlevy@gmail.com)
* @brief Given a sorted array Arr of size N and a number X, you need to find the number of occurrences of X in Arr.
* 
* Example 1:
* 
* Input:
* N = 7, X = 2
* Arr[] = {1, 1, 2, 2, 2, 2, 3}
* Output: 4
* Explanation: 2 occurs 4 times in the
* given array.
* Example 2:
* 
* Input:
* N = 7, X = 4
* Arr[] = {1, 1, 2, 2, 2, 2, 3}
* Output: 0
* Explanation: 4 is not present in the
* given array.
* Your Task:
* You don't need to read input or print anything. Your task is to complete the function count() which takes the array of integers arr, n, and x as parameters and returns an integer denoting the answer.
* If x is not present in the array (arr) then return 0.
* 
* Expected Time Complexity: O(logN)
* Expected Auxiliary Space: O(1)
* 
* Constraints:
* 1 ≤ N ≤ 105
* 1 ≤ Arr[i] ≤ 106
* 1 ≤ X ≤ 106
* @version 0.1
* @date 2023-08-20
*
*
*/
#include <number_of_occurrences/number_of_occurrences.h>

/**
 * @brief if x is present in arr[] then returns the count
 *		  of occurrences of x, otherwise returns 0.
 *          Complexity O(n)
 * 
 * @param arr - Array of integers
 * @param n  - Number of elements in the array
 * @param x - Number to count its occurrences
 * @return int - Number of occurrences of x in arr
 */
int count_linear(int arr[], int n, int x) {
    // At first it looks fairly easy question
    // Brute force approach will run in O(n)
    // Just go through all the elements and count the occurences of x.
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if(arr[i] == x) {
            count++;
        }
    }
    return count;
}

/**
 * @brief if x is present in arr[] then returns the count
 *		  of occurrences of x, otherwise returns 0.
 *          Complexity O(log(n))
 * 
 * @param arr - Array of integers
 * @param n  - Number of elements in the array
 * @param x - Number to count its occurrences
 * @return int - Number of occurrences of x in arr
 */
int count(int arr[], int n, int x) {
    // Now let do it binary search style
    int count = 0;
    int left = 0;
    int right = n - 1;
    int mid = 0;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if(arr[mid] == x) {
            count++;
            break;
        }
        else if(arr[mid] < x) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    // Now we need to check if there are more occurrences of x
    // to the left and to the right of the first occurrence
    // we found.
    // We will do it in O(n) time.
    // We will go to the left and to the right of the first occurrence
    // and count the occurrences of x.
    // We will stop when we will find an element that is not x.
    // We will do it in O(n) time.
    int i = mid - 1;
    while (i >= 0 && arr[i] == x)
    {
        count++;
        i--;
    }
    i = mid + 1;
    while (i < n && arr[i] == x)
    {
        count++;
        i++;
    }
    return count;
}

