import argparse
import os
import sys
import shutil

WORKSPACE_DIR = "workspace"
TEMPLATES_DIR = os.path.join("utils", "templates")


def main(contest_name, num_questions):
    contest_dir = os.path.join(WORKSPACE_DIR, contest_name)
    shutil.copytree(TEMPLATES_DIR, contest_dir,
                    ignore=shutil.ignore_patterns("*.cpp", "*.yaml"))

    solution_template = os.path.join(TEMPLATES_DIR, "atcoder_main.cpp")
    testcases_template = os.path.join(TEMPLATES_DIR, "testcases.yaml")
    for question_id in range(1, num_questions + 1):
        fn_solution = os.path.join(contest_dir, "q%d.cpp" % (question_id))
        fn_testcases = os.path.join(
            contest_dir, "q%d_cases.yaml" % (question_id))
        shutil.copyfile(solution_template, fn_solution)
        shutil.copyfile(testcases_template, fn_testcases)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--contest_name", required=True)
    parser.add_argument("-q", "--num_questions", type=int, default=6)
    args = parser.parse_args()

    main(args.contest_name, args.num_questions)
