#pragma once
/**
 * @file linked_list.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-06
 *
 *
 */

typedef struct Node
{
    int data;
    struct Node *next;

    Node(int x)
    {
        data = x;
        next = nullptr;
    }

} node_t;

/**
 * @brief Create a linked list object
 *
 * @param arr array of integers
 * @param n length of array
 * @return node_t*
 */
node_t *create_linked_list(int arr[], int n);

/**
 * @brief Free linked list
 *
 * @param head
 */
void free_linked_list(node_t *head);

/**
 * @brief Print linked list
 *
 * @param head
 */
void print_linked_list(node_t *head);