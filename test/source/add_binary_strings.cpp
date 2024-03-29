#include <add_binary_strings/add_binary_strings.h>
#include <doctest/doctest.h>
#include <stdlib.h>

#include <bitset>
#include <string>

TEST_CASE("Add binary strings")
{
    using namespace add_binary_strings;

    // Random tests:
    for (int i = 0; i < 5; i++)
    {
        // Generate random binary string from numbers
        long long first_num = rand();
        long long second_num = rand();
        long long sum = first_num + second_num;

        std::string first_string = std::bitset<64>(first_num).to_string();
        std::string second_string = std::bitset<64>(second_num).to_string();
        std::string true_sum_string = std::bitset<64>(sum).to_string();

        MESSAGE("first_string = ", first_string);
        MESSAGE("second_string = ", second_string);
        MESSAGE("true_sum_string = ", true_sum_string);

        // Remove leading zeros
        true_sum_string.erase(0, true_sum_string.find_first_not_of('0'));
        MESSAGE("NO LEADING zeros: true_sum_string = ", true_sum_string);

        CHECK(true_sum_string == add_binary(first_string, second_string));
    }

    // test for when A.len > B.len
    long long first_num = 15;
    long long second_num = 1;
    long long sum = first_num + second_num;

    std::string first_string = std::bitset<4>(first_num).to_string();
    std::string second_string = std::bitset<1>(second_num).to_string();
    std::string true_sum_string = std::bitset<5>(sum).to_string();

    MESSAGE("first_string = ", first_string);
    MESSAGE("second_string = ", second_string);
    MESSAGE("true_sum_string = ", true_sum_string);

    // Remove leading zeros
    true_sum_string.erase(0, true_sum_string.find_first_not_of('0'));
    MESSAGE("NO LEADING zeros: true_sum_string = ", true_sum_string);

    CHECK(true_sum_string == add_binary(first_string, second_string));

    // test for when A.len < B.len
    first_num = 15;
    second_num = 1023;
    sum = first_num + second_num;

    first_string = std::bitset<22>(first_num).to_string();
    second_string = std::bitset<32>(second_num).to_string();
    true_sum_string = std::bitset<64>(sum).to_string();

    MESSAGE("first_string = ", first_string);
    MESSAGE("second_string = ", second_string);
    MESSAGE("true_sum_string = ", true_sum_string);

    // Remove leading zeros
    true_sum_string.erase(0, true_sum_string.find_first_not_of('0'));
    MESSAGE("NO LEADING zeros: true_sum_string = ", true_sum_string);

    CHECK(true_sum_string == add_binary(first_string, second_string));
}
