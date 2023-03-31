#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>

#define ASSERT(x) assert(x)

namespace local_debug {

#define DEFINE_HAS_MEMBER(member_name)                      \
    template <class T>                                      \
    struct has_member_##member_name {                       \
       private:                                             \
        template <class U>                                  \
        static constexpr auto has_member(U&& x)             \
            -> decltype(x.member_name, std::true_type());   \
        static constexpr std::false_type has_member(...);   \
                                                            \
       public:                                              \
        static constexpr bool value =                       \
            decltype(has_member(std::declval<T>()))::value; \
    }

#define DEFINE_HAS_FUNC(func_name)                        \
    template <class T>                                    \
    struct has_func_##func_name {                         \
       private:                                           \
        template <class U>                                \
        static constexpr auto has_func(U&& x)             \
            -> decltype(x.func_name(), std::true_type()); \
        static constexpr std::false_type has_func(...);   \
                                                          \
       public:                                            \
        static constexpr bool value =                     \
            decltype(has_func(std::declval<T>()))::value; \
    }

DEFINE_HAS_FUNC(begin);
DEFINE_HAS_FUNC(val);
DEFINE_HAS_FUNC(dump);
DEFINE_HAS_MEMBER(first);
DEFINE_HAS_MEMBER(second);
template <class T>
inline constexpr bool is_pair_v = (has_member_first<T>::value ||
                                   has_member_second<T>::value);
#undef DEFINE_HAS_MEMBER
#undef DEFINE_HAS_FUNC

template <class T>
void dump(T x) {
    if constexpr (std::is_arithmetic_v<T>) {
        std::cerr << x;
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cerr << "\"" << x << "\"";
    } else if constexpr (is_pair_v<T>) {
        std::cerr << "(";
        dump(x.first);
        std::cerr << ", ";
        dump(x.second);
        std::cerr << ")";
    } else if constexpr (has_func_dump<T>::value) {
        x.dump();
    } else if constexpr (has_func_val<T>::value) {
        dump(x.val());
    } else if constexpr (has_func_begin<T>::value) {
        std::cerr << "{";
        for (auto&& e : x) {
            dump(e);
            std::cerr << ", ";
        }
        if (x.size() > 0) {
            std::cerr << "\e[2D";
        }
        std::cerr << "}";
    } else {
        static_assert([] { return false; }());
    }
}

#define DUMP_HEADER(x)                                                    \
    std::cerr << "\e[1m\e[36m[DUMP: line " << __LINE__ << "]\e[0m " << #x \
              << " : "

#define DUMP(x)                 \
    do {                        \
        DUMP_HEADER(x);         \
        local_debug::dump(x);   \
        std::cerr << std::endl; \
    } while (false)

}  // namespace local_debug
