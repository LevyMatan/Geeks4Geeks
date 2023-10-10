/**
 * @file reverse_alternate_nodes_in_link_list.cpp
 * @brief
 * @version 0.1
 * @date 2023-10-06
 *
 *
 */
#include <doctest/doctest.h>
#include <reverse_alternate_nodes_in_link_list/reverse_alternate_nodes_in_link_list.h>

TEST_CASE("Reverse Alternate Nodes in Link List: Toy Example")
{
    int arr[] = {1, 2, 3, 4, 5};
    node_t *root = create_linked_list(arr, 5);
    rearrange(root);
    CHECK(root->data == 1);
    CHECK(root->next->data == 3);
    CHECK(root->next->next->data == 5);
    CHECK(root->next->next->next->data == 4);
    CHECK(root->next->next->next->next->data == 2);
    CHECK(root->next->next->next->next->next == nullptr);
}