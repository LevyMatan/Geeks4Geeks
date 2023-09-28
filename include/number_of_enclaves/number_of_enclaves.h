#pragma once
/**
 * @file number_of_enclaves.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-28
 *
 *
 */

#include <vector>

using namespace std;

/**
 * @brief Given a 2D array, each cell is 0 (representing sea) or 1 (representing land)
 * A move consists of walking from one land square 4-directionally to another land square, or off
 * the boundary of the grid. Return the number of land squares in the grid for which we cannot walk
 * off the boundary of the grid in any number of moves.
 *
 * @param grid a 2D array of 0's and 1's
 * @return int
 */
int number_of_enclaves(vector<vector<int>> &grid);