import argparse
import os
import shutil

WORKSPACE_DIR = "workspace"
CHECKER_DIR = os.path.join("utils", "checker")
TEMPLATES_DIR = os.path.join("utils", "templates")
TESTCASE_DIR = "testcases"


def generate_testcase_config(question_id, contest_dir):
    config_str = f"""
target: q{question_id}
# eps: 1e5 # 出力が小数の場合は誤差を指定する
samples:
  case1:
    input:
      - "3"
      - "1 2 3"
    output:
      - "6"
  case2:
    input:
      - "4"
      - "1 3 5 7"
    output:
      - "16"
# random:
#   ref: r{question_id}
#   generator: q{question_id}
"""
    with open(os.path.join(contest_dir, TESTCASE_DIR, f"q{question_id}.yaml"), "w") as f:
        f.write(config_str)


def main(contest_name, num_questions):
    contest_dir = os.path.join(WORKSPACE_DIR, contest_name)
    os.makedirs(contest_dir)
    os.makedirs(os.path.join(contest_dir, "src"))
    os.makedirs(os.path.join(contest_dir, "testcases"))
    os.makedirs(os.path.join(contest_dir, "build"))

    shutil.copy(os.path.join(TEMPLATES_DIR, "check.py"), contest_dir)
    shutil.copy(os.path.join(TEMPLATES_DIR, "local_debug.hpp"), contest_dir)
    shutil.copy(os.path.join(TEMPLATES_DIR, "Makefile"), contest_dir)
    shutil.copy(os.path.join(TEMPLATES_DIR, "run.sh"), contest_dir)
    shutil.copytree(
        CHECKER_DIR,
        os.path.join(contest_dir, "checker"),
        ignore=shutil.ignore_patterns("__pycache__"),
    )

    solution_template = os.path.join(TEMPLATES_DIR, "atcoder_main.cpp")
    generator_template = os.path.join(TEMPLATES_DIR, "generator_template.py")
    for question_id in range(1, num_questions + 1):
        fn_solution = os.path.join(contest_dir, "src", f"q{question_id}.cpp")
        fn_ref = os.path.join(contest_dir, "src", f"r{question_id}.cpp")
        fn_generator = os.path.join(contest_dir, TESTCASE_DIR, f"q{question_id}.py")
        shutil.copyfile(solution_template, fn_solution)
        shutil.copyfile(solution_template, fn_ref)
        shutil.copyfile(generator_template, fn_generator)
        generate_testcase_config(question_id, contest_dir)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("contest_name")
    parser.add_argument("num_questions", type=int, default=6)
    args = parser.parse_args()

    main(args.contest_name, args.num_questions)
