import argparse
import os
import subprocess
import sys

import yaml


def print_color(message, color):
    esc = {
        "black": "\033[30m",
        "red": "\033[31m",
        "green": "\033[32m",
        "yellow": "\033[33m",
        "blue": "\033[34m",
        "magenta": "\033[35m",
        "cyan": "\033[36m",
        "white": "\033[37m",
    }
    print("%s\033[1m%s\033[0m" % (esc[color], message))


def list_to_str(l):
    return "\n".join(l)


def normalize_blank(s):
    return " ".join(s.split())


def main(question_name):
    fn_testcases = question_name + "_cases" + ".yaml"
    with open(fn_testcases) as f:
        testcases = yaml.safe_load(f)

    fn_binary = "./" + question_name

    for name, content in testcases["testcases"].items():
        input = list_to_str(content["input"])
        assumption = list_to_str(content["output"])
        cp = subprocess.run([fn_binary], input=input, encoding="utf-8",
                            stdout=subprocess.PIPE)
        output = cp.stdout
        if normalize_blank(output) == normalize_blank(assumption):
            print_color("[%s] Passed" % name, "green")
        else:
            print_color("[%s] Failed" % name, "red")
            print("input:")
            print(input)
            print("output:")
            print(output)
            print("assumption:")
            print(assumption)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-q", "--question_name", required=True)
    args = parser.parse_args()

    main(args.question_name)
