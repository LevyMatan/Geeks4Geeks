/**
 * @file nodes_at_a_given_distance_in_binary_tree.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 *
 */
#include <nodes_at_a_given_distance_in_binary_tree/nodes_at_a_given_distance_in_binary_tree.h>

/**
 * @brief Find all the nodes at a given distance from a target node in a binary tree
 *
 * @param root
 * @param target
 * @param k
 * @return std::vector <int>
 */
std::vector<int> k_distance_nodes(Node* root, Node* target, int k)
{
    std::vector<int> result;
    if (root == nullptr)
    {
        return result;
    }
    if (k == 0)
    {
        result.push_back(root->data);
        return result;
    }
    // Check if target node is at distance k from the current node
    // if (k_distance(root, target, k))
    // {
    //     result.push_back(root->data);
    // }
    // Recursively check left and right subtrees with reduced value of k
    std::vector<int> left = k_distance_nodes(root->left, target, k - 1);
    std::vector<int> right = k_distance_nodes(root->right, target, k - 1);
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}

bool k_distance(Node* root, Node* target, int k)
{
    if (root == nullptr)
    {
        return false;
    }
    if (root == target)
    {
        return k == 0;
    }
    // Recursively check left and right subtrees with reduced value of k
    bool left = k_distance(root->left, target, k - 1);
    bool right = k_distance(root->right, target, k - 1);
    return left || right;
}