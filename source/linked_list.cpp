/**
 * @file linked_list.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-06
 *
 *
 */
#include <fmt/format.h>
#include <linked_list/linked_list.h>

#include <iostream>

/**
 * @brief Create a linked list object
 *
 * @param arr array of integers
 * @param n length of array
 * @return node_t*
 */
node_t *create_linked_list(int arr[], int n)
{
    node_t *head = new node_t(arr[0]);
    node_t *temp = head;
    for (int i = 1; i < n; i++)
    {
        temp->next = new node_t(arr[i]);
        temp = temp->next;
    }
    return head;
}

/**
 * @brief Free linked list
 *
 * @param head
 */
void free_linked_list(node_t *head)
{
    node_t *temp = head;
    while (temp != nullptr)
    {
        node_t *next = temp->next;
        delete temp;
        temp = next;
    }
}

/**
 * @brief Print linked list
 *
 * @param head
 */
void print_linked_list(node_t *head)
{
    node_t *temp = head;
    while (temp != nullptr && temp->next != nullptr)
    {
        std::cout << fmt::format("{} -> ", temp->data);
        temp = temp->next;
    }
    if (temp)
    {
        std::cout << fmt::format("{}", temp->data);
    }
    std::cout << std::endl;
}

int push_back(node_t *head, int data)
{
    node_t *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = new node_t(data);
    return 0;
}

int push_front(node_t **head, int data)
{
    node_t *temp = new node_t(data);
    temp->next = *head;
    *head = temp;
    return 0;
}

int insert_after(node_t *prev_node, int data)
{
    if (prev_node == nullptr)
    {
        return -1;
    }
    node_t *temp = new node_t(data);
    temp->next = prev_node->next;
    prev_node->next = temp;
    return 0;
}

int delete_node(node_t **head, int key)
{
    node_t *temp = *head;
    node_t *prev = nullptr;
    if (temp != nullptr && temp->data == key)
    {
        *head = temp->next;
        delete temp;
        return 0;
    }
    while (temp != nullptr && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        return -1;
    }
    prev->next = temp->next;
    delete temp;
    return 0;
}

int delete_node_at_position(node_t **head, int position)
{
    node_t *temp = *head;
    node_t *prev = nullptr;
    if (position == 0)
    {
        *head = temp->next;
        delete temp;
        return 0;
    }
    for (int i = 0; temp != nullptr && i < position; i++)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        return -1;
    }
    prev->next = temp->next;
    delete temp;
    return 0;
}

int get_length(node_t *head)
{
    int count = 0;
    node_t *temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}
