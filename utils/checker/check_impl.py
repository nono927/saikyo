from .print_utils import print_success, print_failure
from .program import Program
from .testcases import TestCases


def check(
    target: Program,
    testcases: TestCases,
    verbose: bool = False,
) -> dict:
    result_info = dict()

    for case_id, input, expect in testcases:
        actual = target.run(input)

        if actual == expect:
            print_success(f"[{case_id}] Success")
        else:
            print_failure(f"[{case_id}] Failed")
            if verbose:
                print_failure("input:")
                print("\n".join(input.to_list()))
                print_failure("expect:")
                print("\n".join(expect.to_list()))
                print_failure("actual:")
                print("\n".join(actual.to_list()))

        result_info[case_id] = {
            "input": input.to_list(),
            "output": expect.to_list(),
            "output_actual": actual.to_list(),
        }

    return result_info
