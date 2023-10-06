/**
 * @file reverse_alternate_nodes_in_link_list.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-06
 *
 *
 */
#include <reverse_alternate_nodes_in_link_list/reverse_alternate_nodes_in_link_list.h>

void rearrange(struct Node *odd)
{
    struct Node *root = odd;
    struct Node *appendix = nullptr;
    while (odd && odd->next)
    {
        struct Node *to_be_removed = odd->next;
        if (to_be_removed)
        {
            odd->next = to_be_removed->next;
            to_be_removed->next = appendix;
            appendix = to_be_removed;
        }
        odd = odd->next;
    }

    // Connect the appendix to the end of the list
    if (!odd)
    {
        odd = root;
        while (odd && odd->next)
        {
            odd = odd->next;
        }
    }
    odd->next = appendix;
}