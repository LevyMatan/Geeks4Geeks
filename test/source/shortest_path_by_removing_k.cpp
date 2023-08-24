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
    int n = (int)mat.size();
    int m = (int)mat[0].size();
    int k = 0;
    CHECK(shortestPath(mat, n, m, k) == 7);

    mat.push_back(std::vector<int>({0, 1, 1}));
    mat.push_back(std::vector<int>({0, 0, 0}));
    n = (int)mat.size();
    m = (int)mat[0].size();
    CHECK(shortestPath(mat, n, m, k) == 13);
    k = 1;
    CHECK(shortestPath(mat, n, m, k) == 9);

    try
    {
        int num_lines, num_numbers, k_new;
        std::string test_case_filename = "shortest_path_by_removing_k_tc.txt";
        std::string file_path = __FILE__;
        #ifdef _WIN32
        const char dir_sep = '\\';
        #else
        const char dir_sep = '/';
        #endif
        std::string dir_path = file_path.substr(0, file_path.rfind(dir_sep));
        std::string test_case_file_full_path = (dir_path + dir_sep + test_case_filename);
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
        n = (int)matt.size();
        m = (int)matt[0].size();
        CHECK(shortestPath(matt, n, m, k_new) == 45);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
