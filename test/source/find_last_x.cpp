/**
 * @file find_last_x.cpp
 * @brief
 * @version 0.1
 * @date 2023-09-25
 *
 *
 */
#include <doctest/doctest.h>
#include <find_last_x/find_last_x.h>

#include <algorithm>
#include <random>

TEST_CASE("Easy case")
{
    int arr[] = {1, 3, 5, 5, 5, 5, 67, 123, 125};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 5;
    std::vector<int> result = find_last_x::find(arr, n, x);
    CHECK(result[0] == 2);
    CHECK(result[1] == 5);
}

TEST_CASE("Hard case")
{
    const int NUM_OF_TEST_CASES = 100;
    const int MAX_ARRAY_SIZE = 1000000;
    const int MAX_ELEMENT_VALUE = 1000000000;

    for (int i = 0; i < NUM_OF_TEST_CASES; i++)
    {
        int n = rand() % MAX_ARRAY_SIZE + 1;
        int x = rand() % MAX_ELEMENT_VALUE + 1;
        int *arr = new int[n];
        for (int j = 0; j < n; j++)
        {
            arr[j] = rand() % MAX_ELEMENT_VALUE + 1;
        }
        std::sort(arr, arr + n);
        std::vector<int> result = find_last_x::find(arr, n, x);
        std::vector<int> naive_result = find_last_x::find_naive(arr, n, x);
        CHECK(result[0] == naive_result[0]);
        CHECK(result[1] == naive_result[1]);
        delete[] arr;
    }
}