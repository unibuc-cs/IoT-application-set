import argparse

client_getters = {}
ALL_APPS = []
def get_all_clients_apis():
    return {k: v() for k, v in client_getters.items()}

runLocally = 0
portGenerator_current = 9080
def get_localNewAppAddress():
    global portGenerator_current
    outAddr = f"http://localhost:{portGenerator_current}"
    portGenerator_current += 10
    # TOdo : check if the port is available maybe :)

    return outAddr

import smarttv
from smarttv.api import default_api as smarttv_default_api
from smarttv.api.default_api import DefaultApi as SmarttvDefaultApi

def get_smarttv_api() -> SmarttvDefaultApi:
    print(f"Instanciate API client for smarttv")
    configuration = smarttv.Configuration(host = f"http://smarttv:9080" if runLocally == 0 else get_localNewAppAddress())
    api_client = smarttv.ApiClient(configuration)
    return smarttv_default_api.DefaultApi(api_client)


import smartkettle
from smartkettle.api import default_api as smartkettle_default_api
from smartkettle.api.default_api import DefaultApi as SmartkettleDefaultApi

def get_smartkettle_api() -> SmartkettleDefaultApi:
    print(f"Instanciate API client for smartkettle")
    configuration = smartkettle.Configuration(host = f"http://smartkettle:9080" if runLocally == 0 else get_localNewAppAddress())
    api_client = smartkettle.ApiClient(configuration)
    return smartkettle_default_api.DefaultApi(api_client)

import smartoven
from smartoven.api import default_api as smartoven_default_api
from smartoven.api.default_api import DefaultApi as SmartovenDefaultApi

def get_smartoven_api() -> SmartovenDefaultApi:
    print(f"Instanciate API client for smartoven")
    configuration = smartoven.Configuration(host = f"http://smartoven:9080" if runLocally == 0 else get_localNewAppAddress())
    api_client = smartoven.ApiClient(configuration)
    return smartoven_default_api.DefaultApi(api_client)


import windwow
from windwow.api import default_api as windwow_default_api
from windwow.api.default_api import DefaultApi as WindwowDefaultApi

def get_windwow_api() -> WindwowDefaultApi:
    print(f"Instanciate API client for windwow")
    configuration = windwow.Configuration(host = f"http://windwow:9080" if runLocally == 0 else get_localNewAppAddress())
    api_client = windwow.ApiClient(configuration)
    return windwow_default_api.DefaultApi(api_client)


import flowerpower
from flowerpower.api import default_api as flowerpower_default_api
from flowerpower.api.default_api import DefaultApi as FlowerpowerDefaultApi

def get_flowerpower_api() -> FlowerpowerDefaultApi:
    print(f"Instanciate API client for flowerpower")
    configuration = flowerpower.Configuration(host = f"http://flowerpower:9080" if runLocally == 0 else get_localNewAppAddress())
    api_client = flowerpower.ApiClient(configuration)
    return flowerpower_default_api.DefaultApi(api_client)


import smarteeth
from smarteeth.api import default_api as smarteeth_default_api
from smarteeth.api.default_api import DefaultApi as SmarteethDefaultApi

def get_smarteeth_api() -> SmarteethDefaultApi:
    print(f"Instanciate API client for smarteeth")
    configuration = smarteeth.Configuration(host = f"http://smarteeth:9080" if runLocally == 0 else get_localNewAppAddress())
    api_client = smarteeth.ApiClient(configuration)
    return smarteeth_default_api.DefaultApi(api_client)

if __name__ == "__main__":
    argparser = argparse.ArgumentParser(description=__doc__)
    argparser.add_argument(
        '-runLocally', '--runLocally',
        metavar='runLocally',
        type=int,
        default=0,
        help='Run applications locally instead of docker')

    args = argparser.parse_args()
    runLocally = args.runLocally

    client_getters["smartkettle"] = get_smartkettle_api
    ALL_APPS.append("smartkettle")

    client_getters["smarttv"] = get_smarttv_api
    ALL_APPS.append("smarttv")

    client_getters["smartoven"] = get_smartoven_api
    ALL_APPS.append("smartoven")

    client_getters["windwow"] = get_windwow_api
    ALL_APPS.append("windwow")

    client_getters["flowerpower"] = get_flowerpower_api
    ALL_APPS.append("flowerpower")

    client_getters["smarteeth"] = get_smarteeth_api
    ALL_APPS.append("smarteeth")

