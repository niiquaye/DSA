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

bool solution(const std::string& s1, const std::string& s2)
{
    if (s1.size() > s2.size() || s2.empty() || s1.empty()) return false;
    
    std::unordered_map<char, int> map {};
    std::unordered_map<char, int> s1_count {};

    for (const auto elem : s1)
    {
        map[elem]++;
    }
    int have {(int)map.size()};
    int need {0};
    int left {0};

    for (int i = 0; i < s1.size(); i++)
    {
        const char character = s2[i];
        s1_count[character]++;
        if (map.find(character) != map.end() && map[character] == s1_count[character])
        {
            need++;
        }
    }
    
    // first window contains permutation
    if (have == need)
    {
        return true;
    }


    for (int right = 1; right < s2.size() - s1.size() + 1; right++)
    {
        const char left_character = s2[left];
        const char right_character = s2[right + s1.size() - 1];

        // remove left character
        s1_count[left_character]--;
        if (map.find(left_character) != map.end() && map[left_character] - 1 == s1_count[left_character])
        {
            need--;
        }


        // add right character
        s1_count[right_character]++;
        if (map.find(right_character) != map.end() && map[right_character] == s1_count[right_character])
        {
            need++;
        }

        // permutation found
        if (need == have)
        {
            return true;
        }

        // update left pointer
        left++;
 
    }

    return false; 
}

int main(int argc, char* argv[])
{
    std::cout << solution("ab", "eidbaooo") << std::endl;  // true  -> "ba"
    std::cout << solution("ab", "eidboaoo") << std::endl;  // false
    std::cout << solution("adc", "dcda") << std::endl;     // true  -> "dca"
    std::cout << solution("a", "a") << std::endl;          // true
    std::cout << solution("abc", "bbbca") << std::endl;    // true  -> "bca"

}
