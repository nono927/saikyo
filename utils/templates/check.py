import argparse
import importlib
import os

from checker.check_impl import check
from checker.example import Example
from checker.io import load_config, save_config
from checker.program import Program
from checker.testcases import SampleTestCases, DynamicTestCases

BINARY_DIR = "build"
TESTCASE_DIR = "testcases"


def sample_check(target_program, samples, verbose):
    if samples is None:
        return dict()
    testcases = SampleTestCases(samples)
    return check(target_program, testcases, verbose)


def random_check(target_program, config, verbose):
    if config is None:
        return dict()
    importlib.import_module(f"{TESTCASE_DIR}.{config["generator"]}")
    program_ref = Program(os.path.join(BINARY_DIR, config["ref"]))
    testcases = DynamicTestCases(program_ref)
    return check(target_program, testcases, verbose)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("config_path")
    parser.add_argument("-q", "--quiet", action="store_true")
    args = parser.parse_args()

    config = load_config(os.path.join(TESTCASE_DIR, args.config_path))
    target_program = Program(os.path.join(BINARY_DIR, config["target"]))
    if "eps" in config:
        eps = float(config["eps"])
        Example.set_eps(eps)
    verbose = not args.quiet

    sample_results = sample_check(target_program, config.get("samples", None), verbose)
    random_results = random_check(target_program, config.get("random", None), verbose)

    results = dict()
    results["target"] = config["target"]
    if eps := Example.get_eps():
        results["eps"] = eps
    results["samples"] = {**sample_results, **random_results}
    save_config(results, os.path.join(TESTCASE_DIR, f"{args.config_path}_result.yaml"))


if __name__ == "__main__":
    main()
