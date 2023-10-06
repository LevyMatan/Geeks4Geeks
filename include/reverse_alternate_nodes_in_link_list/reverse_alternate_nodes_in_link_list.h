#pragma once
/**
 * @file reverse_alternate_nodes_in_link_list.h
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

void rearrange(struct Node *odd);
