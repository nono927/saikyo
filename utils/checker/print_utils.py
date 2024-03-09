from enum import StrEnum


class Color(StrEnum):
    BLACK = "\033[30m"
    RED = "\033[31m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"
    MAGENTA = "\033[35m"
    CYAN = "\033[36m"
    WHITE = "\033[37m"


def print_color(message: str, color: Color) -> None:
    ESC_RESET = "\033[0m"
    ESC_BOLD = "\033[1m"
    print(f"{color.value}{ESC_BOLD}{message}{ESC_RESET}")


def print_success(message: str) -> None:
    print_color(message, Color.GREEN)


def print_failure(message: str) -> None:
    print_color(message, Color.RED)
