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


std::string brute_force_solution(const std::string& s, const std::string& t)
{
    if (s.empty() || t.empty() || t.size() > s.size()) return "";
    
    std::unordered_multiset<char> multi_set_t {t.begin(), t.end()};
    std::unordered_multiset<char> multi_set_s {};

    auto does_set_contain_other_set = [](std::unordered_multiset<char>& s, 
                                         std::unordered_multiset<char>& t) -> bool
    {
        for (const auto& ch : t)
        {
            if (s.count(ch) < t.count(ch))
                return false;
        }
        return true;
    };

    int min_len {std::numeric_limits<int>::max()};
    int left {0};
    std::string res {""};
    for (int right = 0; right < s.size(); right++)
    {

        multi_set_s.insert(s[right]);

        while (does_set_contain_other_set(multi_set_s, multi_set_t))
        {
            

            auto it = multi_set_s.find(s[left]);
            // ensures we only erase one element in case there are duplicates 'find()' grabs one element at a time
            if (it != multi_set_s.end())
            {
                multi_set_s.erase(it);
            }

            // must update string after each loop iteration as we are trying to reduce the elements in the string
            if (right - left + 1 < min_len)
            {
                res = s.substr(left, right-left+1);
                min_len = right - left + 1;
            }

            left++;
        }


        
    }
    return res;

}



int main(int argc, char*argv[])
{
    std::cout << "BF Minimum Window Substring : " << brute_force_solution("ADOBECODEBANC", "ABC") << std::endl;
    std::cout << "BF Minimum Window Substring : " << brute_force_solution("a", "a") << std::endl;
    std::cout << "BF Minimum Window Substring : " << brute_force_solution("a", "aa") << std::endl;
    return 0;
}