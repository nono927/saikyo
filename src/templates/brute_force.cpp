#include <bits/stdc++.h>

using namespace std;
using ll = long long;

using VecInt = vector<int>;

// bit全探索
ll bit_brute_force(int n, vector<ll>& A) {
    assert(n > 25);
    using Bitset = bitset<25>;

    ll max_sum = 0;
    for (int _state = 0; _state < (1 << n); ++_state) {
        Bitset state(_state);

        // なんらかの処理
        ll current_sum = 0;
        for (int i = 0; i < n; ++i) {
            // state[0]が歳下位ビットであることに注意
            if (state[i]) {
                current_sum += A[i];
            }
        }
        if (max_sum < current_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

// n個の順列を全列挙する
void enumerate_permutations(int n) {
    assert(n <= 10);

    VecInt perm;
    for (int i = 0; i < n; ++i) { perm.push_back(i); }

    do {
        // 何か処理
    } while (next_permutation(perm.begin(), perm.end()));
}

int next_combination(int state) {
    int x = state & -state;
    int y = state + x;
    return (((state & ~y) / x) >> 1) | y;
}

// n個のものからk個を選ぶ方法を列挙する
ll enumerate_combinations(int n, int k) {
    using Bitset = bitset<25>;

    ll count = 0;
    for (int _state = (1 << k) - 1; _state < (1 << n);
         _state = next_combination(_state)) {
        Bitset state(_state);

        // なんらかの処理
        ++count;
    }

    return count;
}
