from abc import ABCMeta, abstractmethod
from collections.abc import Generator, Callable
import functools

from .program import Program
from .example import Example


def example_generator(name: str | None = None, count: int = 1):
    @staticmethod
    def to_string(x) -> str:
        if isinstance(x, list):
            return " ".join(map(str, x))
        return str(x)

    def _example_generator(func: Callable[..., list]):
        @functools.wraps(func)
        def _wrapper(*args, **kwargs) -> Example:
            rows = func(*args, **kwargs)
            rows = list(map(to_string, rows))
            return Example(rows)

        _name = name if name is not None else func.__name__
        DynamicTestCases.add_generator_func(_name, _wrapper, count)
        return _wrapper

    return _example_generator


class TestCases(metaclass=ABCMeta):
    def __iter__(self):
        return self._generator()

    @abstractmethod
    def _generator(self) -> Generator[str, Example, Example]:
        raise NotImplementedError()


class SampleTestCases(TestCases):
    def __init__(
        self, samples: dict, input_key: str = "input", output_key: str = "output"
    ) -> None:
        self.samples = []
        for case_id, content in samples.items():
            input = Example(content[input_key])
            expect = Example(content[output_key])
            self.samples.append((case_id, input, expect))

    def _generator(self) -> Generator[str, Example, Example]:
        for case_id, input, expect in self.samples:
            yield case_id, input, expect


class DynamicTestCases(TestCases):
    __example_generator_funcs = dict()

    def __init__(self, program_expect: Program) -> None:
        self.program_expect = program_expect

    def _generator(self) -> Generator[str, Example, Example]:
        for name, (func, count) in DynamicTestCases.__example_generator_funcs.items():
            for i in range(count):
                caseid = f"{name}{i + 1}"
                input = func()
                expect = self.program_expect.run(input)
                yield caseid, input, expect

    @staticmethod
    def add_generator_func(name: str, func: Callable[..., list], count: int) -> None:
        if name in DynamicTestCases.__example_generator_funcs:
            raise Exception(f"the function named '{name}' is already registered")
        DynamicTestCases.__example_generator_funcs[name] = (func, count)
