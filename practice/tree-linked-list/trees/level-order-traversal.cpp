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


std::vector<std::vector<int>> solution(TreeNode* root)
{
    std::vector<std::vector<int>> level_traversal {};
    std::function<void(TreeNode*)> level_order = [&](TreeNode* node) -> void 
    {
        if (!node) return;

        std::queue<TreeNode*> queue{};
        queue.push(node);

        while(!queue.empty())
        {
            int level {(int)queue.size()};
            std::vector<int> level_nodes {};

            for (int i = 0; i < level; i++)
            {
                auto top = queue.front();
                queue.pop();

                // process node
                level_nodes.push_back(top->val);
            
                // visit neighbours (really just children)
                if (top->left) queue.push(top->left);
                if (top->right) queue.push(top->right);
            }

            level_traversal.push_back(level_nodes);
        }
    };

    level_order(root);
    return level_traversal;
}

int main(int argc, char* argv[])
 {
    std::cout << "Hello World" << std::endl;
    return 0;
 }