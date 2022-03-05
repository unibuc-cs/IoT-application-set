#!/usr/bin/env python3

from os import system, listdir
from sys import argv

if len(argv) < 3:
    print(f"Usage: {argv[0]} <input> <output> [target user] [target group]")
    exit()

input_dir = argv[1]
output_dir = argv[2]
target_user = argv[3] if len(argv) > 3 else 1000
target_group = argv[4] if len(argv) > 4 else 1000

apps = listdir(input_dir)

print(f"Apps: {', '.join(apps)}")

requirements = ""

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
open(f"{output_dir}/all.py", "w").write(importer)
open(f"{output_dir}/__init__.py", "w").write("")

system(f"chown -R {target_user}:{target_group} {output_dir}")