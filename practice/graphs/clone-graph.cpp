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
#include <memory>

class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


std::vector<Node> transform_list_graph(const std::vector<std::vector<int>>& list)
{
    if (list.empty()) return {};

    std::vector<Node> node_vec(list.size()); // !!important must pre-allocate memory!!

    for (int node = 0; node < list.size(); node++)
    {
        node_vec[node].val = node;
        
        for (const auto n : list[node])
        {
            node_vec[node].neighbors.push_back(&node_vec[n-1]);
        }
    }

    return node_vec;
    
}

bool are_graph_equal(Node* root_a, Node* root_b, std::unordered_map<Node*, Node*>& visited)
{
    if (!root_a && !root_b) return true;
    if (root_a->val != root_b->val) return false;
    if (root_a == root_b) return false; // ensures a deep copy

    // If already visited, ensure it maps to same clone node
    if (visited.find(root_a) != visited.end()) return visited[root_a] == root_b;
    visited.insert({root_a, root_b}); // using a map ensures structures that nodes map 1-1 as opposed to set
                                      // if graph is undirected than a set can be used


    if (root_a->neighbors.size() != root_b->neighbors.size()) return false;

    for (int child = 0; child < root_a->neighbors.size(); child++)
    {
        if (!are_graph_equal(root_a->neighbors[child], root_b->neighbors[child], visited)) return false;
 
    }

    return true;
}


Node* solution(Node* root)
{
    if (!root) return nullptr;

    std::queue<Node*> queue {};
    queue.push(root);

    std::unordered_map<Node*, Node*> clone_map {};

    clone_map[root] = new Node(root->val); // first node

    while (!queue.empty())
    {
        Node* curr = queue.front();
        queue.pop();


        for (const auto children : curr->neighbors)
        {
            // if child does not exist - clone it and then push child to queue to continue BFS
            if (clone_map.find(children) == clone_map.end())
            {
                clone_map[children] = new Node(children->val);
                queue.push(children);
            }
            clone_map[curr]->neighbors.push_back(clone_map[children]); // need to push back clone_map[children] and 
                                                                       //just children as we need to ensure deep copy
        }

    }

    return clone_map[root];
}

int main(int argc, char* argv[])
{
    std::vector<Node> graph = transform_list_graph({ {2,4},{1,3},{2,4},{1,3}  });
    Node* first_node = &graph.at(0);

    Node* root_node = solution(first_node);

    std::unordered_map<Node*, Node*> visited;
    bool result = are_graph_equal(first_node, root_node, visited);

    std::cout << "IS SAME: " << result << std::endl;
}