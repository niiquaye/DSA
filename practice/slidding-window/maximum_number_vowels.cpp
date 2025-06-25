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

int solution(const std::string& s, int k)
{
    if (s.empty()) return 0;

    std::unordered_set<char> set({'a', 'e', 'i', 'o', 'u'});
    // compute first window
    int sum {0};
    for (int i = 0; i < k; i++)
    {
        sum += (set.find(s[i])!= set.end())? 1 : 0;
    }

    int max = sum;

    // compute k-1 remaining windows
    for (int i = k; i < s.size(); i++)
    {
        sum += ((set.find(s[i-k])!= set.end())? -1 : 0); // remove old element from window size k if vowel
        sum += ((set.find(s[i])!= set.end())? 1 : 0);  // add new element to window size k if vowel
        max = std::max(max, sum);
    }
    return max;
}

int main(int argc, char* argv[])
{
    std::cout << "Maximum Number of Vowels: " << solution({"abciiidef"}, 3) << std::endl;
    std::cout << "Maximum Number of Vowels: " << solution({"aeiou"}, 2) << std::endl;
    std::cout << "Maximum Number of Vowels: " << solution({"leetcode"}, 3) << std::endl;
}