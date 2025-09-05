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

std::vector<int> solution(TreeNode* root)
{
    std::vector<int> traversal {};
    std::function<void(TreeNode*)> in_order = [&](TreeNode* node) -> void 
    {
        if (!node) return;
        in_order(node->left);
        traversal.push_back(node->val);
        in_order(node->right);

    };

    in_order(root);
    return traversal;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0;
}