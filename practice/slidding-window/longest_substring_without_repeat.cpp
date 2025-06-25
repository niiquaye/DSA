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


int optimal_solution(const std::string& s)
{
    if (s.empty()) return 0;

    std::unordered_set<char> set {};
    int left {0};
    int max_len {std::numeric_limits<int>::min()};

    for (int right = 0; right < s.size(); right++)
    {
        const char right_character = s[right];
        // try removing left most char until we can insert right character - dynamic sliding window
        while(set.find(right_character) != set.end())
        {
            const char left_char = s[left];
            set.erase(left_char);
            left++;
        }

        set.insert(right_character);
        max_len = std::max(max_len, right - left +1);

    }
    return max_len;
}

int main(int argc, char* argv[])
{
    std::cout << "Longest Substring Without Repeating Characters: " << optimal_solution("abcabcbb") << std::endl;
    std::cout << "Longest Substring Without Repeating Characters: " << optimal_solution("bbbbb") << std::endl;
    std::cout << "Longest Substring Without Repeating Characters: " << optimal_solution("pwwkew") << std::endl;
    return 0;
}