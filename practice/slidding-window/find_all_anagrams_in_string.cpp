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


inline void print_vec(const std::vector<int>& array)
{
    std::cout << "[";
    for (const auto elem : array)
    {
        std::cout << elem << ", ";
    }
    std::cout << "]";
    std::cout << "" << std::endl;
}

std::vector<int> solution(const std::string& s, const std::string& p)
{
    if (p.size() > s.size() || p.empty() || s.empty()) return {};

    std::unordered_map<char, int> map {};
    std::unordered_map<char, int> p_count {};

    for (const auto elem : p)
    {
        map[elem]++;
    }

    int need {(int)map.size()};
    int have {0};
    int left {0};

    std::vector<int> result {};

    // initialize static window
    for (int i = 0; i < p.size(); i++)
    {
        const char character = s[i];
        if (map.find(character) != map.end())
        {
            p_count[character]++;
        }

        if (p_count.find(character) != p_count.end() && p_count[character] == map[character])
        {
            have++;
        }
    }

    if (have == need)
    {
        result.push_back(left);
    }

    // fixed sliding window
    for (int right = 1; right < s.size() - p.size() + 1; right++)
    {
        const char left_character = s[left];
        const char right_character = s[right+p.size()-1];

        // remove left character from window
        p_count[left_character]--;
        if (map.find(left_character) != map.end() && p_count[left_character] == map[left_character] - 1)
        {
            have--;
        }

        // add right character to window
        p_count[right_character]++;

        // check if adding and removing characters in window still keeps anagram
        if (map.find(right_character) != map.end() && p_count[right_character] == map[right_character])
        {
            have++;
        }


        left++; // update here since we pushed left character out we need to update it before we add to vec
        if (have == need)
        {
            result.push_back(left);
        }

    }

    return result;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;
    print_vec(solution("cbaebabacd", "abc")); // ➝ {0, 6}
    print_vec(solution("abab", "ab"));        // ➝ {0, 1, 2}
    print_vec(solution("a", "a"));            // ➝ {0}
    print_vec(solution("a", "b"));            // ➝ {}
    print_vec(solution("baa", "aa"));         // ➝ {1}
    print_vec(solution("aaaa", "aa"));        // ➝ {0, 1, 2}

    return 0;
}