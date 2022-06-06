#!/usr/bin/env python3

import argparse
from os import system, listdir
import sys

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input", help="input dir", required=True)
parser.add_argument("-o", "--output", help="output dir", required=True)
parser.add_argument("-u", "--target_user", help="target-user", required=False, default=1000)
parser.add_argument("-g", "--target_group", help="target-group", required=False, default=1000)
parser.add_argument("-a", "--apps", nargs="*", help="app list", required=False, default="")

args = parser.parse_args()

input_dir = args.input
output_dir = args.output
target_user = args.target_user
target_group = args.target_group

if args.apps == "":
    ignored_apps = {"app_template", "philips", "vacuumcleaner"}
    apps = [app for app in listdir(input_dir) if app not in ignored_apps]
else:
    apps = args.apps

print(f"Apps: {', '.join(apps)}")

requirements = """\
-e ./mergedclients
"""

importer_template = """\

import NAME
from NAME.api import default_api as NAME_default_api
from NAME.api.default_api import DefaultApi as NAME_CAPITALDefaultApi

def get_NAME_api() -> NAME_CAPITALDefaultApi:
    print(f"Instanciate API client for NAME")
    configuration = NAME.Configuration(host = f"http://NAME:9080")
    api_client = NAME.ApiClient(configuration)
    return NAME_default_api.DefaultApi(api_client)

client_getters["NAME"] = get_NAME_api
ALL_APPS.append("NAME")

"""

importer = """\

client_getters = {}
ALL_APPS = []
def get_all_clients_apis():
    return {k: v() for k, v in client_getters.items()}

"""

setupfile = """\
from setuptools import setup, find_packages  # noqa: H301

NAME = "mergedclients"
VERSION = "1.0.0"

setup(
    name=NAME,
    version=VERSION,
    description="Merged Clients",
    url="",
    keywords=[],
    python_requires=">=3.6",
    packages=find_packages(exclude=["test", "tests"]),
    include_package_data=True,
)
"""

generator = "java -jar /opt/openapi-generator/modules/openapi-generator-cli/target/openapi-generator-cli.jar"
for app in apps:
    app_path = f"{input_dir}/{app}"
    system(f"{generator} generate -i {app_path}/openapi.yaml \
        -g python \
        -o {output_dir}/{app} \
        -c {app_path}/generator_config.json\
        ")

    requirements += f"-e ./{app}\n"

    importer += importer_template.replace("NAME_CAPITAL", app.capitalize()).replace("NAME", app)
open(f"{output_dir}/requirements.txt", "w").write(requirements)

# Generate a package which imports all the generated clients
packagepath = f"{output_dir}/mergedclients"
packagecodepath = f"{packagepath}/mergedclients"
system(f"mkdir -p {packagecodepath}")
open(f"{packagecodepath}/all.py", "w").write(importer)
open(f"{packagecodepath}/__init__.py", "w").write("")
open(f"{packagepath}/setup.py", "w").write(setupfile)

system(f"chown -R {target_user}:{target_group} {output_dir}")
