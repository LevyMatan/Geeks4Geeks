/**
 * @file find_four_sum.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-25
 *
 *
 */
#include <find_four_sum/find_four_sum.h>

#include <algorithm>
/**
 * @brief Given an array A of integers and another number K. Find all the unique quadruple from the
 given array that sums up to K.

 * Also note that all the quadruples which you return should be internally sorted, ie for any
 quadruple [q1, q2, q3, q4] the following should follow: q1 <= q2 <= q3 <= q4.

 *
 * @param arr
 * @param k
 * @return std::vector<std::vector<int> >
 */
std::vector<std::vector<int> > find_four_sum(std::vector<int> &arr, int k)
{
    std::vector<std::vector<int> > result;

    int n = (int)arr.size();
    if (n < 4)
    {
        return result;
    }

    std::sort(arr.begin(), arr.end());

    for (int i = 0; i < n - 3; i++)
    {
        if (i > 0 && arr[i] == arr[i - 1])
        {
            continue;
        }
        for (int j = i + 1; j < n - 2; j++)
        {
            if (j > i + 1 && arr[j] == arr[j - 1])
            {
                continue;
            }
            int left = j + 1;
            int right = n - 1;
            while (left < right)
            {
                int sum = arr[i] + arr[j] + arr[left] + arr[right];
                if (sum == k)
                {
                    result.push_back({arr[i], arr[j], arr[left], arr[right]});
                    left++;
                    right--;
                    while (left < right && arr[left] == arr[left - 1])
                    {
                        left++;
                    }
                    while (left < right && arr[right] == arr[right + 1])
                    {
                        right--;
                    }
                }
                else if (sum < k)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }
    }

    return result;
}