from sys import argv
from os import system, listdir

enable = True if len(argv) > 1 and argv[1] == "enable" else False

for f in listdir("./bug_unpatches"):
    if 'patch' not in f: continue
    print(f"{'Enabling' if enable else 'Disabling'} bug {f}...")

    cmd = f"git apply {'-R' if not enable else ''} ./bug_unpatches/{f}"
    print(cmd)
    system(cmd)
