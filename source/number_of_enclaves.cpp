/**
 * @file number_of_enclaves.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-28
 *
 *
 */
#include <number_of_enclaves/number_of_enclaves.h>

typedef enum cell_type_e
{
    SEA = 0,
    LAND = 1
} cell_type_t;

/**
 * @brief Set current cell given by (i,j) as SEA.
 * Continue to mark all adjacent (up down, left right) land cells as SEA.
 * Using the DFS algorithm.
 *
 * @param grid a 2D array of 0's and 1's
 * @param i row index
 * @param j column index
 */
static void mark_land_as_sea(vector<vector<int>> &grid, int i, int j)
{
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();

    if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == SEA)
    {
        return;
    }

    grid[i][j] = SEA;

    mark_land_as_sea(grid, i + 1, j);
    mark_land_as_sea(grid, i - 1, j);
    mark_land_as_sea(grid, i, j + 1);
    mark_land_as_sea(grid, i, j - 1);
}

/**
 * @brief Given a 2D array, each cell is 0 (representing sea) or 1 (representing land)
 * A move consists of walking from one land square 4-directionally to another land square, or off
 * the boundary of the grid. Return the number of land squares in the grid for which we cannot walk
 * off the boundary of the grid in any number of moves.
 *
 * Algorithm: Scan all the edges of the grid, and land cell found mark as water, and continue
 * marking all the adjacent land cells as water. When done, count the number of land cells left.
 * Only need to scan the inner square of the grid.
 * @param grid a 2D array of 0's and 1's
 * @return int
 */
int number_of_enclaves(vector<vector<int>> &grid)
{
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();

    for (int i = 0; i < rows; i++)
    {
        if (grid[i][0] == LAND)
        {
            mark_land_as_sea(grid, i, 0);
        }
        if (grid[i][cols - 1] == LAND)
        {
            mark_land_as_sea(grid, i, cols - 1);
        }
    }

    for (int j = 0; j < cols; j++)
    {
        if (grid[0][j] == LAND)
        {
            mark_land_as_sea(grid, 0, j);
        }
        if (grid[rows - 1][j] == LAND)
        {
            mark_land_as_sea(grid, rows - 1, j);
        }
    }

    int result = 0;
    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            if (grid[i][j] == LAND)
            {
                result++;
            }
        }
    }

    return result;
}