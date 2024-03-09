from checker.generators import *
from checker.testcases import example_generator


@example_generator(name="random", count=10)
def f1():
    n = generate_int(1, 11)
    A = generate_intarray(n, 1, 101)
    return [n, A]