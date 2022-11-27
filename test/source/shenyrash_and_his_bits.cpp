#include <doctest/doctest.h>
#include <geeks4geeks/version.h>
#include <shenyrash_and_his_bits/shenyrash_and_his_bits.h>
#include <stdlib.h>

namespace shenyrash_and_his_bits
{
    // Brute force manner
    int count_set_bits_in_number(long long x)
    {
        int count_set_bits = 0;
        for (int i = 0; i < 64; i++)
        {
            if (x & 1ULL)
            {
                count_set_bits++;
            }
            x = x >> 1U;
        }

        return count_set_bits;
    }

    long long count_numbers_with_n_set_bits_brute_force(long long x)
    {
        int num_of_set_bits = count_set_bits_in_number(x);
        // printf("Testing %lld which has %d bits set\n", x, num_of_set_bits);
        long long count_nums = 0;
        while (x > 0)
        {
            x--;
            if (num_of_set_bits == count_set_bits_in_number(x))
            {
                // printf("%lld also have %d bits set\n", x, num_of_set_bits);
                count_nums++;
            }
        }

        return count_nums;
    }
}  // namespace shenyrash_and_his_bits
TEST_CASE("Shenyrash and His Bits")
{
    for (long long test_case = 0; test_case < 5; test_case++)
    {
        long long N = rand() % 10000;
        MESSAGE("Test case N = ", N);
        CHECK(shenyrash_and_his_bits::count(N)
              == shenyrash_and_his_bits::count_numbers_with_n_set_bits_brute_force(N));
    }

    // Test for full rank number
    long long N = 1023;
    MESSAGE("Test case N = ", N);
    CHECK(shenyrash_and_his_bits::count(N)
          == shenyrash_and_his_bits::count_numbers_with_n_set_bits_brute_force(N));
}
