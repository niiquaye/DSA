#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate


int solution(const std::vector<int>& prices)
{
    if (prices.empty()) return 0;

    int buy1 {std::numeric_limits<int>::min()};
    int buy2 {std::numeric_limits<int>::min()};
    int sell1 {0};
    int sell2 {0};

    for (int i = 0; i < prices.size(); i++)
    {
        int stock_price = prices[i];

        buy1 = std::max(buy1, -stock_price); // when conducting first buy price is negative because you spend money to buy the stock
        sell1 = std::max(sell1, buy1+stock_price); // since buy1 is negative we then add it to curr stock price to see profit
        buy2 = std::max(buy2, sell1-stock_price); // sell1 is positive less stock price to see profit
        sell2 = std::max(sell2, buy2+stock_price);

    }
    return sell2;
}

// best time to buy sell stock after k transactions
int solution_k(const std::vector<int>& prices, int k)
{
    if (prices.empty()) return 0;

    std::vector<int> buy(k, std::numeric_limits<int>::min());
    std::vector<int> sell(k, 0);

    for (int i = 0; i < prices.size(); i++)
    {
        int stock_price = prices[i];

        for (int j = 0; j < k; j++)
        {

            int profit_after_buy = (j == 0)? -stock_price : sell[j-1] + stock_price;
            buy[j] = std::max(buy[j], profit_after_buy);

            sell[j] = std::max(sell[j], buy[j] + stock_price);
        }
    }
    return sell.at(k-1);
}

int main(int argv, char* argc[])
{
    std::cout << "Best Time to Buy Sell Stock III: " << solution({3,3,5,0,0,3,1,4}) << std::endl;
    std::cout << "Best Time to Buy Sell Stock III: " << solution({1,2,3,4,5}) << std::endl;
    std::cout << "Best Time to Buy Sell Stock III: " << solution({7,6,4,3,1}) << std::endl;

    return 0;
}