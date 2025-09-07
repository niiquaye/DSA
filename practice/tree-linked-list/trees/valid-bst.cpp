#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate
#include <string>
#include <unordered_set>
#include <deque>
#include <queue>
#include <map>
#include <memory>
#include <limits>

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


bool solution(TreeNode* root)
{
    std::function<bool(TreeNode* node)> valid = [&](TreeNode* node) -> bool 
    {
        if (!node) return true;
        if (node->left && node->val <= node->left->val) return false;
        if (node->right && node->val > node->right->val) return false;
        return valid(node->right) && valid(node->left);


    };
    bool res = valid(root);
    return res;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0;
}