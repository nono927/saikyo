#include <algorithm>
#include <cassert>
#include <tuple>
#include <vector>

template <class T1, class T2>
void lexicographical_sort(std::vector<T1>& v1, std::vector<T2>& v2) {
    assert(v1.size() == v2.size());
    std::vector<std::tuple<T1, T2>> v;
    for (size_t i = 0; i < v1.size(); ++i) {
        v.emplace_back(v1[i], v2[i]);
    }
    std::sort(v.begin(), v.end());
    for (size_t i = 0; i < v1.size(); ++i) {
        tie(v1[i], v2[i]) = v[i];
    }
}

template <class T1, class T2, class T3>
void lexicographical_sort(std::vector<T1>& v1, std::vector<T2>& v2,
                          std::vector<T3>& v3) {
    assert(v1.size() == v2.size());
    assert(v1.size() == v3.size());
    std::vector<std::tuple<T1, T2, T3>> v;
    for (size_t i = 0; i < v1.size(); ++i) {
        v.emplace_back(v1[i], v2[i], v3[i]);
    }
    std::sort(v.begin(), v.end());
    for (size_t i = 0; i < v1.size(); ++i) {
        tie(v1[i], v2[i], v3[i]) = v[i];
    }
}

// 区間のソート
// leftsの昇順にソート
// leftsが同じ場合，rightsの降順にソート
template <class T>
void interval_sort(std::vector<T>& lefts, std::vector<T>& rights) {
    const int m = lefts.size();
    assert(rights.size() == m);
    for (int i = 0; i < m; ++i) {
        rights[i] *= -1;
    }
    lexicographical_sort(lefts, rights);
    for (int i = 0; i < m; ++i) {
        rights[i] *= -1;
    }
}