# FLOWER POWER  

Using Cmake as a build tool with WSL Ubuntu 20.04 bash in a VSCode editor.  

## Installing prerequisites

1. Firstly, update your apt  

```sh
sudo apt update  
sudo apt upgrade  
```  

2. Install pistache (our HTTP server) as described  

```sh
sudo add-apt-repository ppa:pistache+team/unstable
sudo apt install libpistache-dev
```

3. Install Mosquitto (our MQTT sub/pub/broker).

```sh
sudo apt install mosquitto mosquitto-clients libmosquitto-dev 
```

4. Install RapidJSON as our JSON reading library.  

```sh
sudo apt-get install -y rapidjson-dev
```

5. Install Open MP as our multithreading library.

```sh
sudo apt-get install libomp-dev
```

6. Install cmake and make  

```sh
sudo apt install make  
sudo apt install cmake  
```  

## Build  

Go to the /build folder and enter `cmake .. ; make` in the bash terminal.

## Running the binary

1. In build/demo/ the file named `main` is our binary executable.
2. Enter `./main` to run our binary file.
3. In your browser go to `localhost:9080/test` and see if it works.

## HTTP testing  

1. Open a new bash terminal so we can make some curl requests (but keep the old terminal with the server running).
2. Type  `curl -X GET http://localhost:9080/settings/soilType`, you should receive the answer "soilType is Negru".
3. Type `curl -X PUT http://localhost:9080/settings/soilType/Roz`, you should receive "soilType was set to Roz".
4. Try some setting that do not exist, like `curl -X GET http://localhost:9080/settings/mortiSiRanitiInGhiveci`, you should receive "mortiSiRanitiInGhiveci was not found".  

## MQTT Testing

1. Open a MQTT broker daemon, in any wsl bash run:  

```sh
sudo service mosquitto start
```

2. Now, publish something and see if our MQTT server is listening.

```sh
mosquitto_pub -t 'test' -m 'Nu-i caruta ca mertanu'
```

The message shall appear in the opened server.

## How to add code?

As long as you don't add files or add god knows what weird libraries, you can simple go to the build/ folder and run `make` after each change (we don't have to run `cmake ..` again) and the code will compile with the last changes.  

 But if you want to add files to be compiled or additional libraries, we'll need to get our hands dirty and touch the CMakeLists.txt files.

## Installing libraries  

 You can install the library in ubuntu and link them in demo/CMakeLists.txt in the function `target_link_libraries(main SmartPotLib pistache crypto ssl pthread DESIRED_INSTALLED_LIBRARY)`. DONE  
 If you need to download the library folder and use it in our programme separately from the ubuntu then I'll look into it another time cuz it's late now and I need to test this approach.

## Cleaning the build

For now you can simply delete ALL the contents of build/ and rerun the cmake for a fresh build.

## GG

This is just a test.
