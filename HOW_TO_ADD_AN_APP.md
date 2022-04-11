How do you add an application to this dataset?
===

You need to provide a few configuration files if you want your app to be integrated properly in the network. Take a look at the [template](./apps/app_template)
or at any other [app](./apps) if you need a complete example. Now, the steps to integrate your app are the following: 

1. Create an OpenAPI specification for your HTTP endpoints. 
2. Provide the necessary configuration for OpenAPI client generation. The package name must match the name of your application and the name of your root folder. An example configration could be found here [generator_config.json](./apps/app_template/generator_config.json). The file MUST be named the same, `generator_config.json`.
3. Create an AsyncAPI specification for your MQTT endpoints. (optional, it is not used at the moment)
4. Provide a script for dependency installition. The script must be aimed towards an Ubuntu system (the only one supported right now). The script
MUST be named [deps_ubuntu.sh](./apps/app_template/deps_ubuntu.sh) and it MUST be in the root folder of your application.
4. Provide a build script for at least `x86` and `armv7`. The script MUST be named [build.sh](apps/app_template/build.sh). (if your app does not need to be built, you could provide an empty script or omit it entrirely)
5. Provide a script for running your application, named [run.sh](./apps/app_template/run.sh) which takes a `<port>` argument.
6. Add an entry to [change_ports.sh](./hub/change_ports.sh) to ease local deployment. (optional)
7. Provide a Dockerfile (preferably based on Ubuntu) which will build and run your application like in this [example Dockerfile](./apps/app_template/Dockerfile).
8. Add an entry for your application to [docker-compose.dev.yml](./docker-compose.dev.yml). It should be similar to this:
```
# === Application <app name> ===
  <app name>:
    labels:
      - type=application
    ports:
        - '<some external port>:5000'
    restart: always
    build:
      context: ./apps/<your app name>
    networks:
      - iot_dataset
```
8. Copy your application to `./apps/<your app name>`. The folder name MUST match the package name from step 2.

**Note:** All scripts MUST be marked as executable.
