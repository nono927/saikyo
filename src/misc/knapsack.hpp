#include <algorithm>
#include <cassert>
#include <vector>

template <class value_t, class weight_t>
value_t knapsack(std::vector<value_t>& values, std::vector<weight_t>& weights,
                 weight_t max_weight) {
    const int n = values.size();
    assert(n == weights.size());

    std::vector<value_t> dp(max_weight + 1);
    for (int i = 0, i < n; ++i) {
        for (weight_t w = max_weight, w >= 0; --w) {
            if (w - weights[i] < 0) {
                break;
            }
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return *std::max_element(dp.begin(), dp.end());
}