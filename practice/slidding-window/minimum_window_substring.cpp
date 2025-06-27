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
#include <array>


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

// fully optimal
std::string optimal_solution_t(const std::string& s, const std::string& t)
{
    if (s.empty() || t.empty() || t.size() > s.size()) return "";

    // 128 ASCII characters
    std::array<int, 128> freq {};
    std::array<int, 128> window {};

    int left {0};
    int have {0};

    int need {0};
    for (const auto elem: t)
    {
        // increment for unique characters only
        if (freq[elem] == 0)
        {
            need++;
        }
        freq[elem]++;
    }
    
 

    int min_len {std::numeric_limits<int>::max()};
    int min_start {0};
    std::string res {""};

    for (int right = 0; right < s.size(); right++)
    {
        const char character = s[right];
        window[character]++;

        if ( freq[character] && freq[character] == window[character])
        {
            have++;
        }

        // try reducing substring now that we found the largest substring to contain all characters
        while (have == need)
        {
            // 1. construct sub string that contains all valid characters
            if (right - left + 1 < min_len)
            {
                // min_len = right - left + 1;
                // res = s.substr(left, right-left+1);

                min_start = left;
                min_len = right - left + 1;
            }

            // 2. try removing left most character in 's'
            const char left_most_character = s[left];
            window[left_most_character]--;

            // 3. check if we removed any crucial characters - if so decrement 'have' counter
            if ( freq[left_most_character] && window[left_most_character] < freq[left_most_character])
            {
                have--;
            }

            // 4. increment left pointer to update window size
            left++; 

        }
    }

    // compute result string at the end instead of each iteration in for loop as strings can be quite LARGE!!! - this change prevented MLE
    return (min_len == std::numeric_limits<int>::max())? "" : s.substr(min_start, min_len);
}

// optimal but MLE 
std::string optimal_solution(const std::string& s, const std::string& t)
{
    if (s.empty() || t.empty() || t.size() > s.size()) return "";

    std::unordered_map<char, int> freq {};
    std::unordered_map<char, int> window {};

    int left {0};
    int have {0};

    for (const auto elem: t)
        freq[elem]++;
    
    int need {(int)freq.size()};

    int min_len {std::numeric_limits<int>::max()};

    std::string res {""};

    for (int right = 0; right < s.size(); right++)
    {
        const char character = s[right];
        window[character]++;

        // must check frequency count first before comparing values at the keys to insure the map does not insert 
        // a 0 value at character if it does not exist in the freq map - cannot use .at() because it will throw 
        // and cannot use '[]' by itself due to its ability to create elements that do not exist in map
        if ( freq.count(character) && freq[character] == window[character])
        {
            have++;
        }

        // try reducing substring now that we found the largest substring to contain all characters
        while (have == need)
        {
            // 1. construct sub string that contains all valid characters
            if (right - left + 1 < min_len)
            {
                min_len = right - left + 1;
                res = s.substr(left, right-left+1);
            }

            // 2. try removing left most character in 's'
            const char left_most_character = s[left];
            window[left_most_character]--;

            // 3. check if we removed any crucial characters - if so decrement 'have' counter
            if (freq.count(left_most_character) && window[left_most_character] < freq[left_most_character])
            {
                have--;
            }

            // 4. increment left pointer to update window size
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

    std::cout << "BF Minimum Window Substring : " << optimal_solution("ADOBECODEBANC", "ABC") << std::endl;
    std::cout << "BF Minimum Window Substring : " << optimal_solution("a", "a") << std::endl;
    std::cout << "BF Minimum Window Substring : " << optimal_solution("a", "aa") << std::endl;

    std::cout << "BF Minimum Window Substring : " << optimal_solution_t("ADOBECODEBANC", "ABC") << std::endl;
    std::cout << "BF Minimum Window Substring : " << optimal_solution_t("a", "a") << std::endl;
    std::cout << "BF Minimum Window Substring : " << optimal_solution_t("a", "aa") << std::endl;
    return 0;
}