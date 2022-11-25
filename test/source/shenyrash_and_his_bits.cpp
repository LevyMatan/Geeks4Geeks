#include <doctest/doctest.h>
#include <geeks4geeks/version.h>
#include <shenyrash_and_his_bits/shenyrash_and_his_bits.h>


namespace shenyrash_and_his_bits
{
    //Brute force manner
    int count_set_bits_in_number(long long x)
    {
        int count_set_bits = 0;
        for (size_t i = 0; i < 64; i++)
        {
            if(x & 1ULL)
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
        while(x > 0)
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
}
TEST_CASE("Shenyrash and His Bits") {

    for(long long N = 3; N < 1000; N++)
    {
        MESSAGE("Test case N = ", N);
        CHECK(shenyrash_and_his_bits::count(N) == shenyrash_and_his_bits::count_numbers_with_n_set_bits_brute_force(N));
    }
}

// TEST_CASE("Greeter version") {
//   static_assert(std::string_view(GEEKS4GEEKS_VERSION) == std::string_view("1.0"));
//   CHECK(std::string(GEEKS4GEEKS_VERSION) == std::string("1.0"));
// }
