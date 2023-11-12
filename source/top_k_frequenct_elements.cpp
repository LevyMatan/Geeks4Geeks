/**
 * @file top_k_frequenct_elements.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-05
 *
 *
 */
#include <top_k_frequenct_elements/top_k_frequenct_elements.h>

#include <algorithm>
#include <map>
// include pair:
#include <utility>

namespace top_k_frequenct_elements
{

    /**
     * @brief Given a non empty array nums[] of integers of length N, find the top k elements which
     * have the highest frequency in the array. If two numbers have same frequencies, then the
     * larger number should be given more preference.
     *
     * @param nums
     * @param k
     * @return vector<int>
     */
    vector<int> topK(vector<int>& nums, int k)
    {
        // Step 1: create a frequency map
        std::map<int, int> freq;
        for (int i = 0; i < (int)nums.size(); i++)
        {
            auto it = freq.find(nums[i]);
            if (it != freq.end())
            {
                freq[nums[i]]++;
            }
            else
            {
                freq[nums[i]] = 1;
            }
        }

        vector<int> res;

        // Step 2: sort the freq map by value
        vector<std::pair<int, int>> sorted_freq;
        for (auto it = freq.begin(); it != freq.end(); it++)
        {
            sorted_freq.push_back(*it);
        }
        sort(sorted_freq.begin(), sorted_freq.end(),
             [](std::pair<int, int> a, std::pair<int, int> b)
             {
                 if (a.second != b.second) return a.second > b.second;
                 return a.first > b.first;
             });

        // Step 3: return the top k elements
        for (int i = 0; i < k; i++)
        {
            res.push_back(sorted_freq[i].first);
        }

        return res;
    }

}  // namespace top_k_frequenct_elements