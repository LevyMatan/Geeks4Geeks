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

/**
 * @brief Add node to the end of the linked list
 *
 * @param head
 * @param data
 * @return int
 */
int push_back(node_t *head, int data);

/**
 * @brief Add node to the beginning of the linked list
 *
 * @param head
 * @param data
 * @return int
 */
int push_front(node_t **head, int data);

/**
 * @brief Add node after a given node
 *
 * @param prev_node
 * @param data
 * @return int
 */
int insert_after(node_t *prev_node, int data);

/**
 * @brief Remove node with given key
 *
 * @param head
 * @param key
 * @return int
 */
int delete_node(node_t **head, int key);

/**
 * @brief Remove node at given position
 *
 * @param head
 * @param position
 * @return int
 */
int delete_node_at_position(node_t **head, int position);

/**
 * @brief Get the length of the linked list
 *
 * @param head
 * @return int
 */
int get_length(node_t *head);
