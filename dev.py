#!/usr/bin/env python3
from sys import argv
from os import listdir, system

apps = listdir('./apps')
ports = {
    "flowerpower": 9081,
    "smartkettle": 9082,
    "smarttv": 9083,
    "windwow": 9084,
    "smarteeth": 9085
}

def usage():
    print("--- Helper script for development ---")
    print(f"Usage: {argv[0]} <command> [application]")
    print(f"Apps: {', '.join(apps)}")
    print("Commands:")
    print(" - reload    Rebuilds and restarts and app")
    print(" - stop      Stops the specified app")
    print(" - add_hosts Add hostnames to /etc/hosts (*nix only)")
    exit()


if "-h" in argv or len(argv) < 2:
    usage()

command = argv[1]
app = argv[2] if len(argv) >= 3 else None
container_name = f"{app}_dev"


def reload():
    system(f"docker kill {container_name}")
    system(f"docker build ./apps/{app} -t {app}")
    system(f"docker run -p{ports[app]}:9080 --rm --name {container_name} -d {app}")


def stop():
    system(f"docker stop {container_name}")


def add_hosts():
    for host in apps:
        sudo_echo(f"127.0.0.1 {host}", "/etc/hosts")

def sudo_echo(text, dest):
    system(f"echo '{text}' | sudo tee -a {dest}")

cmds = {
    "reload": reload,
    "stop": stop,
    "add_hosts": add_hosts,
}

cmds[command]()