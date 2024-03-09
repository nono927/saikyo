import os

import yaml


def load_config(filename: str) -> dict:
    if os.path.splitext(filename)[1] != ".yaml":
        filename += ".yaml"
    with open(filename, "r") as f:
        config = yaml.safe_load(f)
    return config


def save_config(config: dict, filename: str) -> None:
    outdir, _ = os.path.split(filename)
    os.makedirs(outdir, exist_ok=True)
    with open(filename, "w") as f:
        yaml.safe_dump(config, f, sort_keys=False)
