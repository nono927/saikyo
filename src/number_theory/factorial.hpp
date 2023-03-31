#include <atcoder/all>
#include <vector>

// 階乗を計算するクラス
class Factorial {
    using value_t = atcoder::modint998244353;
    int num_elements;
    std::vector<value_t> factorial;
    std::vector<value_t> inverse_factorial;

    void extend(int new_size) {
        factorial.resize(new_size);
        inverse_factorial.resize(new_size);
        for (int i = num_elements; i < new_size; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }
        inverse_factorial[new_size - 1] = factorial[new_size - 1].inv();
        for (int i = new_size - 1; i > num_elements; --i) {
            inverse_factorial[i - 1] = inverse_factorial[i] * i;
        }
        num_elements = new_size;
    }

   public:
    Factorial(int num_elements)
        : num_elements(1), factorial(1), inverse_factorial(1) {
        factorial[0] = 1;
        inverse_factorial[0] = 1;
        extend(num_elements);
    }

    // n! を計算する
    value_t fact(int n) {
        if (n >= num_elements) {
            extend(n + 1);
        }
        return factorial[n];
    }

    // 1/n! を計算する
    value_t ifact(int n) {
        if (n >= num_elements) {
            extend(n + 1);
        }
        return inverse_factorial[n];
    }

    // 二項係数 nCk を計算する
    value_t binom(int n, int k) { return fact(n) * ifact(k) * ifact(n - k); }
};