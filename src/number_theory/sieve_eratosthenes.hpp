#include <vector>

// 0以上n未満の整数に対して，素数かどうかを判定する．
// 戻り値のi番目の要素は，iが素数の時に限りtrueである．
std::vector<bool> sieve_eratosthenes(int n) {
    std::vector<bool> is_primes(n, true);
    is_primes[0] = false;
    is_primes[1] = false;
    for (int p = 2; p < n; ++p) {
        if (!is_primes[p]) {
            continue;
        }
        for (int m = 2; p * m < n; ++m) {
            is_primes[p * m] = false;
        }
    }
    return is_primes;
}
