#!/usr/bin/env python3
from sys import argv
from os import listdir, system

apps = listdir('./apps')


def usage():
    print("--- Helper script for development ---")
    print(f"Usage: {argv[0]} <command> <application>")
    print(f"Apps: {', '.join(apps)}")
    print("Commands:")
    print(" - reload Rebuilds and restarts and app")
    print(" - stop   Stops the specified app")
    exit()


if "-h" in argv or len(argv) < 3:
    usage()

command = argv[1]
app = argv[2]
container_name = f"{app}_dev"


def reload():
    system(f"docker kill {container_name}")
    system(f"docker build ./apps/{app} -t {app}")
    system(f"docker run --rm --name {container_name} -d {app}")


def stop():
    system(f"docker stop {container_name}")


cmds = {
    "reload": reload,
    "stop": stop,
}

cmds[command]()
