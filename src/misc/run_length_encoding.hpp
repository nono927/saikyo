#include <cassert>
#include <string>
#include <utility>
#include <vector>

// 入力のランレングス圧縮を求め，(要素, 連続する長さ) の列を返す．
std::vector<std::pair<char, int>> run_length_encoding(std::string S) {
    if (S.empty()) {
        return std::vector<std::pair<char, int>>();
    }

    S += S.back() + 1;
    int len = 1;
    char c = S[0];
    std::vector<std::pair<char, int>> ret;
    for (size_t i = 1; i < S.size(); ++i) {
        if (S[i - 1] == S[i]) {
            ++len;
        } else {
            ret.emplace_back(c, len);
            c = S[i];
            len = 1;
        }
    }
    return ret;
}

// 入力のランレングス圧縮を求め，(要素, 連続する長さ) の列を返す．
template <class T>
std::vector<std::pair<T, int>> run_length_encoding(std::vector<T> vec) {
    if (vec.empty()) {
        return std::vector<std::pair<T, int>>();
    }

    vec.push_back(vec.back() + 1);
    int len = 1;
    T c = vec[0];
    std::vector<std::pair<T, int>> ret;
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] == vec[i]) {
            ++len;
        } else {
            ret.emplace_back(c, len);
            c = vec[i];
            len = 1;
        }
    }
    return ret;
}