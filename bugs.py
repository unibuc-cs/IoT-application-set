"""
Script to enable and disable bugs.
Usage: python3 bugs.py <"enable"|"disable"> ["step"]
    enable/disable: apply or revert git patches
    step: interactive mode
"""

from sys import argv
from os import system, listdir

enable = True if len(argv) > 1 and argv[1] == "enable" else False
step = True if len(argv) > 2 and argv[2] == "step" else False

for f in listdir("./bug_unpatches"):
    if 'patch' not in f: continue
    print(f"{'Enabling' if enable else 'Disabling'} bug {f}...")

    cmd = f"git apply {'-R' if not enable else ''} ./bug_unpatches/{f}"
    print(cmd)
    system(cmd)

    if step:
        input("Press enter to continue...")
