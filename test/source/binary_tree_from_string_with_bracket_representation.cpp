#include <binary_tree_from_string_with_bracket_representation/binary_tree_from_string_with_bracket_representation.h>
#include <doctest/doctest.h>
#include <geeks4geeks/version.h>

#include <string>

TEST_CASE("Construct Binary Tree from String with bracket representation")
{
    using namespace binary_tree_from_string_with_bracket_representation;
    std::string str = "1(2)(45)";
    Node* p_res = treeFromString(str);
    CHECK(p_res->data == 1);
    CHECK(p_res->left->data == 2);
    CHECK(p_res->right->data == 45);

    delete p_res->left;
    delete p_res->right;
    delete p_res;
}
