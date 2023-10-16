#pragma once
/**
 * @file nodes_at_a_given_distance_in_binary_tree.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 *
 */

#include <fmt/format.h>

#include <vector>

typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;

/**
 * @brief Find all the nodes at a given distance from a target node in a binary tree
 *
 * @param root
 * @param target
 * @param k
 * @return std::vector <int>
 */
std::vector<int> k_distance_nodes(Node* root, int target, int k);
