#pragma once

#include <cassert>
#include <string>
#include <vector>

using ll = long long;

// 数字からなる文字列をvectorに変換する．
std::vector<ll> digits_string_to_vector(std::string& S) {
    std::vector<ll> V;
    for (auto&& c : S) {
        assert(c >= '0' && c <= '9');
        V.push_back(c - '0');
    }
    return V;
}

// 0-9の数値からなるvectorを文字列に変換する．
std::string digits_vector_to_string(std::vector<ll>& V) {
    std::string S;
    for (auto&& x : V) {
        assert(x >= 0 && x <= 9);
        S.push_back('0' + x);
    }
    return S;
}