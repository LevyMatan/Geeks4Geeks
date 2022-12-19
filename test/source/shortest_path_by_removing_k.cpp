#include <doctest/doctest.h>
#include <fmt/format.h>
#include <shortest_path_by_removing_k/shortest_path_by_removing_k.h>

#include <fstream>
#include <iostream>
#include <vector>

TEST_CASE("shortest_path_by_removing_k")
{
    using namespace shortest_path_by_removing_k;

    std::vector<std::vector<int>> mat;
    mat.push_back(std::vector<int>({0, 1, 0}));
    mat.push_back(std::vector<int>({0, 1, 1}));
    mat.push_back(std::vector<int>({0, 0, 0}));
    mat.push_back(std::vector<int>({0, 1, 0}));
    mat.push_back(std::vector<int>({1, 1, 0}));
    mat.push_back(std::vector<int>({0, 0, 0}));
    int n = mat.size();
    int m = mat[0].size();
    int k = 0;
    MESSAGE("n = %d, m = %d, k = %d\n", n, m, k);
    CHECK(shortestPath(mat, mat.size(), mat[0].size(), k) == 7);

    mat.push_back(std::vector<int>({0, 1, 1}));
    mat.push_back(std::vector<int>({0, 0, 0}));
    MESSAGE("n = %d, m = %d, k = %d\n", n, m, k);
    CHECK(shortestPath(mat, mat.size(), mat[0].size(), k) == 13);
    CHECK(shortestPath(mat, mat.size(), mat[0].size(), 1) == 9);

    try
    {
        int num_lines, num_numbers, k_new;
        std::string test_case_filename = "shortest_path_by_removing_k_tc.txt";
        std::string file_path = __FILE__;
        std::string dir_path = file_path.substr(0, file_path.rfind("/"));
        std::string test_case_file_full_path = (dir_path + "/" + test_case_filename);
        std::ifstream big_testcase(test_case_file_full_path, std::ifstream::in);
        if (!big_testcase.is_open())
        {
            throw fmt::format("Failed to open Test Case file: {}\n", test_case_file_full_path);
        }
        // Read the first line of the file
        big_testcase >> num_lines >> num_numbers >> k_new;
        std::cout << "num of lines: " << num_lines << std::endl;
        std::vector<std::vector<int>> matt(num_lines, std::vector<int>(num_numbers));
        for (int i = 0; i < num_lines; ++i)
        {
            for (int j = 0; j < num_numbers; ++j)
            {
                int number;
                big_testcase >> number;
                matt[i][j] = number;
            }
        }
        big_testcase.close();
        CHECK(shortestPath(matt, matt.size(), matt[0].size(), k_new) == 45);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
