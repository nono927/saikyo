import subprocess
from pathlib import Path

from .example import Example


class Program:
    def __init__(self, binary_path: str):
        self.binary_path = Path(binary_path).resolve(strict=True)

    def name(self) -> str:
        return str(self.binary_path.relative_to(Path.cwd()))

    def run(self, input: Example) -> Example:
        input_str = "\n".join(input.to_list())
        cp = subprocess.run(
            [self.binary_path],
            input=input_str,
            encoding="utf-8",
            stdout=subprocess.PIPE,
        )
        output = cp.stdout.splitlines()
        return Example(output)
