/**
 * @file making_a_large_island.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-16
 *
 *
 */
#include <making_a_large_island/making_a_large_island.h>

#include <unordered_map>
#include <unordered_set>

static void create_islands(vector<vector<int>>& grid, int i, int j, int island_id,
                           unordered_map<int, int>& island_sizes)
{
    int num_of_rows = (int)grid.size();
    int num_of_cols = (int)grid[0].size();
    if (i < 0 || j < 0 || i >= num_of_rows || j >= num_of_cols || grid[i][j] != 1)
    {
        return;
    }
    if (grid[i][j] == 1)
    {
        grid[i][j] = island_id;
        island_sizes[island_id]++;
        create_islands(grid, i + 1, j, island_id, island_sizes);
        create_islands(grid, i - 1, j, island_id, island_sizes);
        create_islands(grid, i, j + 1, island_id, island_sizes);
        create_islands(grid, i, j - 1, island_id, island_sizes);
    }
}
/**
 * @brief
 *
 * @param grid
 * @return int
 */
int largest_island(vector<vector<int>>& grid)
{
    unordered_map<int, int> island_sizes;
    island_sizes[0] = 0;
    int num_of_rows = (int)grid.size();
    int num_of_cols = (int)grid[0].size();
    int island_id = 2;

    // Create islands
    for (int row = 0; row < num_of_rows; row++)
    {
        for (int col = 0; col < num_of_cols; col++)
        {
            if (grid[row][col] == 1)
            {
                island_sizes[island_id] = 0;
                create_islands(grid, row, col, island_id, island_sizes);
                island_id++;
            }
        }
    }

    int max_island_size = 0;
    for (auto& island : island_sizes)
    {
        max_island_size = max(max_island_size, island.second);
    }

    // Check what is the max size achielvable by setting one water as land
    for (int row = 0; row < num_of_rows; row++)
    {
        for (int col = 0; col < num_of_cols; col++)
        {
            if (grid[row][col] == 0)
            {
                // get sizes of all islands around this water
                unordered_set<int> islands_around;
                if (row > 0)
                {
                    islands_around.insert(grid[row - 1][col]);
                }
                if (row < num_of_rows - 1)
                {
                    islands_around.insert(grid[row + 1][col]);
                }
                if (col > 0)
                {
                    islands_around.insert(grid[row][col - 1]);
                }
                if (col < num_of_cols - 1)
                {
                    islands_around.insert(grid[row][col + 1]);
                }
                int current_island_size = 1;
                for (auto& island : islands_around)
                {
                    current_island_size += island_sizes[island];
                }
                max_island_size = max(max_island_size, current_island_size);
            }
        }
    }

    return max_island_size;
}