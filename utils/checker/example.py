class Example:
    __eps = None

    def __init__(self, rows: list[str]):
        rows = list(map(lambda x: x.strip().replace("  ", " ").split(" "), rows))
        self.rows = rows

    def __eq__(self, __value: object) -> bool:
        assert isinstance(__value, Example)
        if Example.__eps is None:
            return self.rows == __value.rows
        return self.__eq_float(__value)

    def __eq_float(self, __value: object) -> bool:
        if len(self.rows) != len(__value.rows):
            return False
        for row1, row2 in zip(self.rows, __value.rows):
            l1 = list(map(float, row1))
            l2 = list(map(float, row2))
            if len(l1) != len(l2):
                return False
            for f1, f2 in zip(l1, l2):
                if not Example.__float_eq(f1, f2):
                    return False
        return True

    def to_list(self):
        return list(map(lambda x: " ".join(x), self.rows))

    @staticmethod
    def get_eps():
        return Example.__eps

    @staticmethod
    def set_eps(eps: float | None):
        if eps is not None:
            assert isinstance(eps, float)
            assert eps > 0
        Example.__eps = eps

    @staticmethod
    def __float_eq(x1: float, x2: float):
        return abs(x1 - x2) < Example.__eps * max(1.0, abs(x1), abs(x2))
