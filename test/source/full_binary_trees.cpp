#include <doctest/doctest.h>
#include <full_binary_trees/full_binary_trees.h>

TEST_CASE("Count the Number of Full Binary Trees")
{
    using namespace full_binary_trees;
    MESSAGE("First test case");
    long long int arr[] = {2, 4, 8, 12};
    /**
     * [1]
     *   4
     *  / \
     * 2   2
     *
     * [2]
     *   8
     *  / \
     * 2   4
     *
     * [3]
     *   8
     *  / \
     * 4   2
     *
     * [4]
     *        8
     *       / \
     *      4   2
     *     / \
     *    2   2
     *
     * [5]
     *        8
     *       / \
     *      2   4
     *         / \
     *        2   2
     *
     * [6]
     * 2
     *
     * [7]
     * 4
     *
     * [8]
     * 8
     *
     * [9]
     * 12
     */
    CHECK(numoffbt(arr, 4) == 9);

    MESSAGE("Second test case");
    long long int arr2[] = {3, 5, 28};
    /**
     * [1]
     *      3
     * [2]
     *      5
     * [3]
     *      28
     */

    CHECK(numoffbt(arr2, 3) == 3);
}
