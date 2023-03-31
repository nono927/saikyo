#include <cassert>
#include <utility>
#include <vector>

// 写像 i -> vec[i] で定まる数列（初期値 = start）のサイクルを検出し，
// (サイクルに到達するまでのステップ数，サイクル長) を出力する．
std::pair<int, int> find_cycle(std::vector<int>& vec, int start) {
    auto next_pos = [&](int x) {
        assert(x >= 0 && x < (int)vec.size());
        return vec[x];
    };

    int s = next_pos(start);
    int t = next_pos(next_pos(start));
    while (s != t) {
        s = next_pos(s);
        t = next_pos(next_pos(t));
    }

    int nsteps_to_cycle = 0;
    t = start;
    while (s != t) {
        s = next_pos(s);
        t = next_pos(t);
        ++nsteps_to_cycle;
    }

    s = next_pos(s);
    t = next_pos(next_pos(t));
    int cycle_length = 1;
    while (s != t) {
        s = next_pos(s);
        t = next_pos(next_pos(t));
        ++cycle_length;
    }

    return {nsteps_to_cycle, cycle_length};
}
