#pragma once

#include <atcoder/modint>
#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace local_debug {

const char* ESC_DEFAULT = "\e[0m";
const char* ESC_BOLD = "\e[1m";
const char* ESC_CYAN = "\e[36m";

template <class T>
concept Tuple = requires(T a) { std::tuple_size<T>::value; };

template <class T>
concept Container = requires(T a) {
    a.begin();
    a.end();
} && !std::same_as<T, std::string>;

template <Tuple T, std::size_t N>
void dump_tuple(T x, bool not_first);
template <Container T>
void dump_container(const T container, const char lbrace, const char rbrace);

// =================
// dump functions
// =================

template <class T>
void dump(T x) {
    static_assert([] { return false; }());
}

void dump(bool x) { std::cerr << (x ? "true" : "false"); }

template <std::integral T>
void dump(T x) {
    std::cerr << x;
}

template <std::floating_point T>
void dump(T x) {
    std::cerr << x;
}

void dump(std::string x) { std::cerr << '"' << x << '"'; }

void dump(std::vector<bool> x) {
    bool not_first = false;
    std::cerr << '[';
    for (auto&& e : x) {
        if (not_first) std::cerr << ", ";
        dump((bool)e);
        not_first = true;
    }
    std::cerr << ']';
}

template <class T>
void dump(std::vector<T> x) {
    dump_container(x, '[', ']');
}

template <Tuple T>
void dump(T x) {
    std::cerr << "(";
    dump_tuple<T, 0>(x, false);
    std::cerr << ")";
}

template <class T>
    requires std::derived_from<T, atcoder::internal::modint_base>
void dump(T x) {
    dump(x.val());
}

template <Container T>
void dump(T x) {
    dump_container(x, '{', '}');
}

// ===================
// helper functions
// ===================

template <Tuple T, std::size_t N>
void dump_tuple(T x, bool not_first) {
    if constexpr (N >= std::tuple_size<T>::value) {
        return;
    } else {
        if (not_first) std::cerr << ", ";
        dump(std::get<N>(x));
        dump_tuple<T, N + 1>(x, true);
    }
}

template <Container T>
void dump_container(const T container, const char lbrace, const char rbrace) {
    bool not_first = false;
    std::cerr << lbrace;
    for (auto&& x : container) {
        if (not_first) std::cerr << ", ";
        dump(x);
        not_first = true;
    }
    std::cerr << rbrace;
}

}  // namespace local_debug

// =========
// macros
// =========

#define ASSERT(x) assert(x)

#define DUMP_HEADER(x)                                          \
    std::cerr << local_debug::ESC_BOLD << local_debug::ESC_CYAN \
              << "[DUMP: line " << __LINE__ << "] "             \
              << local_debug::ESC_DEFAULT << #x << " : "

#define DUMP(x)                 \
    do {                        \
        DUMP_HEADER(x);         \
        local_debug::dump(x);   \
        std::cerr << std::endl; \
    } while (false)
