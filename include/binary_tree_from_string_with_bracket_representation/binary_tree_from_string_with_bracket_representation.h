#pragma once
#include <string>
/**
 * @brief Construct Binary Tree from String with bracket representation
 * Construct a binary tree from a string consisting of parenthesis and integers.
 * The whole input represents a binary tree.
 * It contains an integer followed by zero, one or two pairs of parenthesis.
 * The integer represents the roots value and a pair of parenthesis contains
 * a child binary tree with the same structure.
 * Always start to construct the left child node of the parent first if it exists.
 *
 * Example 1:
 *
 * Input: "1(2)(3)"
 * Output: 2 1 3
 * Explanation:
 *            1
 *           / \
 *          2   3
 * Explanation: first pair of parenthesis contains
 * left subtree and second one contains the right
 * subtree. Inorder of above tree is "2 1 3".
 * Example 2:
 *
 * Input: "4(2(3)(1))(6(5))"
 * Output: 3 2 1 4 5 6
 * Explanation:
 *            4
 *          /   \
 *         2     6
 *        / \   /
 *       3   1 5
 *
 * URL:
 * https://practice.geeksforgeeks.org/problems/construct-binary-tree-from-string-with-bracket-representation/1
 */
namespace binary_tree_from_string_with_bracket_representation {

    /**
     * @brief Node struct for a simple binary tree.
     *
     */
    class Node {
      public:
        int data;
        Node *left, *right;
        Node(int data) {
            this->data = data;
            this->left = this->right = NULL;
        }
    };

    Node *treeFromString(std::string str);
}  // namespace binary_tree_from_string_with_bracket_representation