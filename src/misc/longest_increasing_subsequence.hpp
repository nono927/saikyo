#include <algorithm>
#include <limits>
#include <vector>

// 最長（狭義）増加部分列の長さを求める．
// 出力のi番目の要素は，入力のi番目が末尾であるLISの長さである．
template <class T>
std::vector<int> longest_increasing_subsequence(const std::vector<T>& vec) {
    const int n = vec.size();
    std::vector<int> lis_length(n);
    std::vector<T> last_element;
    last_element.push_back(-std::numeric_limits<T>::lowest());
    for (int i = 0; i < n; ++i) {
        // 広義LISを求めたい場合はupper_boundを使う
        auto itr =
            lower_bound(last_element.begin(), last_element.end(), vec[i]);
        int pos = distance(last_element.begin(), itr);
        if (itr == last_element.end()) {
            last_element.push_back(vec[i]);
        } else {
            last_element[pos] = vec[i];
        }
        lis_length[i] = pos;
    }
    return lis_length;
}
