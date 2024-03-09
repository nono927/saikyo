import heapq
import random

# ===========
# Sequence
# ===========


# 半開区間 [low:high] に含まれる整数をランダムに返す。
def generate_int(low: int, high: int) -> int:
    assert low < high
    return random.randint(low, high - 1)


# 半開区間 [low:high] に含まれる整数をn個ランダムに返す。
def generate_intarray(n: int, low: int, high: int) -> list[int]:
    return [generate_int(low, high) for i in range(n)]


# 半開区間 [low:high] に含まれる整数をn個ランダムに返す。
def generate_distinct_intarray(n: int, low: int, high: int) -> list[int]:
    return random.sample(range(low, high), n)


# 長さnの順列をランダムに生成する。
def generate_permutation(n: int, start_from_one: bool = True) -> list[int]:
    perm = range(1, n + 1) if start_from_one else range(n)
    return random.sample(list(perm), n)


# 長さnの狭義単調増加な数列をランダムに生成する。
def generate_increasing_intarray(n: int, low: int, high: int) -> list[int]:
    return sorted(generate_distinct_intarray(n, low, high))


# 長さnの広義単調増加な数列をランダムに生成する。
def generate_non_decreasing_intarray(n: int, low: int, high: int) -> list[int]:
    a = generate_increasing_intarray(n, low, high + n - 1)
    return [x - i for i, x in enumerate(a)]


# ==========
# String
# ==========


# 長さnの文字列をランダムに生成する。
def generate_string(n: int, kinds: int = 26, upper_case: bool = False) -> str:
    a = ord("A") if upper_case else ord("a")
    return "".join(map(lambda x: chr(a + x), generate_intarray(n, 0, kinds)))


# 長さnの数字列をランダムに生成する。
def generate_digits(
    n: int, include_zero: bool = True, enable_leading_zero: bool = False
) -> str:
    low = 0 if include_zero else 1
    digits = generate_intarray(n, low, 10)
    if not enable_leading_zero:
        digits[0] = generate_int(1, 10)
    return "".join(map(str, digits))


# ========
# Graph
# ========


def _prufer_decode(n: int, prufer_code: list[int]) -> list[int, int]:
    degree = [1 for i in range(n)]
    for i in prufer_code:
        degree[i] += 1

    heap = [i for i, d in enumerate(degree) if d == 1]
    heapq.heapify(heap)

    edges = []
    for i in prufer_code:
        j = heapq.heappop(heap)
        edges.append([i, j])
        degree[i] -= 1
        degree[j] -= 1
        if degree[i] == 1:
            heapq.heappush(heap, i)
        if degree[j] == 1:
            heapq.heappush(heap, j)

    u = heapq.heappop(heap)
    v = heapq.heappop(heap)
    edges.append([u, v])

    return edges


# 頂点数nの木をランダムに生成する。
def generate_tree(n: int) -> list[int, int]:
    assert n >= 2
    prufer_code = generate_intarray(n - 2, 0, n)
    edges = _prufer_decode(n, prufer_code)
    random.shuffle(edges)
    edges = [[u + 1, v + 1] for (u, v) in edges]
    return edges


# 頂点数nの重み付き木をランダムに生成する。
def generate_weighted_tree(n: int, low: int, high: int) -> list[int, int, int]:
    tree_edges = generate_tree(n)
    weights = generate_intarray(n - 1, low, high)
    return [[u, v, w] for (u, v), w in zip(tree_edges, weights)]


# 頂点数n、辺数mの連結な無向グラフをランダムに生成する。
def generate_connected_graph(n: int, m: int) -> list[int, int]:
    assert n - 1 <= m <= n * (n - 1) // 2

    mst_edges = generate_tree(n)
    mst_edges = [sorted([x - 1, y - 1]) for x, y in mst_edges]
    edge_set = set([x * n + y for x, y in mst_edges])

    nsamples = min(m * 2 + n, n * n)
    for i in random.sample(range(n * n), nsamples):
        if len(edge_set) == m:
            break
        u, v = sorted([i // n, i % n])
        if u < v:
            edge_set.add(u * n + v)

    edges = [[i // n, i % n] for i in edge_set]
    random.shuffle(edges)

    edges = [[x + 1, y + 1] for x, y in edges]
    return edges


# 頂点数n、辺数mの連結な重みつき無向グラフをランダムに生成する。
def generate_connected_weighted_graph(
    n: int, m: int, low: int, high: int
) -> list[int, int, int]:
    graph = generate_connected_graph(n, m)
    weights = generate_intarray(m, low, high)
    wgraph = [[u, v, w] for (u, v), w in zip(graph, weights)]
    return wgraph
