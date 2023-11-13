/**
 * @file linked_list.cpp
 * @brief
 * @version 0.1
 * @date 2023-10-06
 *
 *
 */
#include <doctest/doctest.h>
#include <linked_list/linked_list.h>

TEST_CASE("Linked List: Standalone Tests")
{
    int arr[] = {1, 2, 3, 4, 5};
    node_t *head = create_linked_list(arr, 5);
    CHECK(head->data == 1);
    CHECK(head->next->data == 2);
    CHECK(head->next->next->data == 3);
    CHECK(head->next->next->next->data == 4);
    CHECK(head->next->next->next->next->data == 5);
    CHECK(head->next->next->next->next->next == nullptr);

    print_linked_list(head);

    push_back(head, 6);
    CHECK(head->next->next->next->next->next->data == 6);

    push_front(&head, 0);
    CHECK(head->data == 0);

    insert_after(head->next, 12);
    CHECK(head->next->next->data == 12);

    delete_node(&head, 12);
    CHECK(head->next->next->data == 2);

    delete_node_at_position(&head, 0);
    CHECK(head->data == 1);
    CHECK(head->next->data == 2);

    int list_length = get_length(head);
    CHECK(list_length == 6);

    free_linked_list(head);
}