/**
 * @file excel_column_name.cpp
 * @brief
 * @version 0.1
 * @date 2023-10-02
 *
 *
 */
#include <doctest/doctest.h>
#include <excel_column_name/excel_column_name.h>
#include <utils/debug.h>

TEST_CASE("Get Excel Column Number from Column Name")
{
    std::string column_name("A");
    long long int column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);

    column_name = "AA";
    column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);
    std::string colum_name_computed = get_excel_column_name(column_number);
    CHECK_EQ(column_name, colum_name_computed);

    column_name = "ZA";
    column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);
    colum_name_computed = get_excel_column_name(column_number);
    CHECK_EQ(column_name, colum_name_computed);

    column_name = "ZZ";
    column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);
    colum_name_computed = get_excel_column_name(column_number);
    CHECK_EQ(column_name, colum_name_computed);

    column_name = "AAA";
    column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);
    colum_name_computed = get_excel_column_name(column_number);
    CHECK_EQ(column_name, colum_name_computed);

    column_name = "ABC";
    column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);
    colum_name_computed = get_excel_column_name(column_number);
    CHECK_EQ(column_name, colum_name_computed);

    column_name = "Z";
    column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);
    colum_name_computed = get_excel_column_name(column_number);
    CHECK_EQ(column_name, colum_name_computed);

    column_name = "ZGDSTA";
    column_number = get_excel_column_number(column_name);
    debug_print("For Column Name: '%s', Column Number: %lld\n", column_name.c_str(), column_number);
    colum_name_computed = get_excel_column_name(column_number);
    CHECK_EQ(column_name, colum_name_computed);
}