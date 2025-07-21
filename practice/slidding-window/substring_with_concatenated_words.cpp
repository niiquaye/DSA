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

std::vector<int> solution(const std::string& s, std::vector<std::string>& words)
{

    if (words.empty() || s.empty() || 
        words[0].size() > s.size() || 
        (s.size() < words.size() * words[0].size())) return {};
    
    std::unordered_map<std::string, int> map {};
    std::unordered_map<std::string, int> words_count {};

    for (const auto elem : words)
    {
        map[elem]++;
    }

    int need {(int)map.size()};
    int have{0};

    int left {0}; // left pointer

    int word_size {words[0].size()}; // assume every word in 'words' vector is the same size

    std::vector<int> result {};

    // initialize first window containing the first 'words.size()' amount of words in substring - fixed window
    for (int i = 0; i < words.size(); i++)
    {
        std::string word {s.substr(i, word_size)};
        words_count[word]++;

        if (words_count.find(word) != words_count.end() && words_count[word] == map[word])
        {
            have++;
        }
        
    }

    if (have == need)
    {
        result.push_back(left);
    }

    int right_start = {words.size()*words[0].size()-1};

    // fixed sliding window - except we move window over by 'word_size' amount
    for (int right = right_start; right < s.size() - word_size; right+= word_size)
    {
        std::string left_word {s.substr(left, word_size)}; // word to eject
        std::string right_word {s.substr(right, word_size)}; // word to add

        words_count[left_word]--;
        if (words_count.find(left_word) != words_count.end() && words_count[left_word] == map[left_word]-1)
        {
            have--;
        }

        words_count[right_word]++;
        if (words_count.find(right_word) != words_count.end() && words_count[right_word] == map[right_word])
        {
            have++;
        }

        if (have == need)
        {
            left++;
            result.push_back(left);
        }
    }

    return result;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}