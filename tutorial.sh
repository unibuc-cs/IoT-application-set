#!/bin/bash

echo "=== IoT applications set for benchmarking testing tools and methods ==="
echo "                         Built by SASHA team"
echo " More about our past publications at https://unibuc-cs.github.io/river/"
echo ""
echo ""

if ! command -v docker &> /dev/null || ! command -v docker-compose &> /dev/null || ! command -v python3 &> /dev/null
then
    echo "[!] docker, docker-compose and python3 must be installed on your system."
    exit
fi


echo "This script will walk you through the features of the application set and it will take a few minutes."
echo ""

### Helpers ###
function yn_prompt {
    read answer
    if ! [ "$answer" != "${answer#[Yy]}" ]
    then
        echo "Bye bye. Exiting..."
    fi
}
###

echo -e "\n\n\n"
echo "### ### ### ### ###"
echo -n "1. Building the application set using docker containers (will take about 10-15 minutes). Proceed? (y/n) "
yn_prompt

set -x
python3 -m pip install -r requirements.txt --user # requirements for utility scripts
./dev init                                        # initialize the environment
./dev generate-clients                            # generate HTTP clients for communicating with the apps
./dev docker-build-all                            # build all the apps
set +x

echo -e "\n\n\n"
echo "### ### ### ### ###"
echo -n "2. We will start the virtual network of the application set. Proceed? (y/n) "
yn_prompt

set -x
./dev docker-start-all-detached
sleep 3
set +x

echo ""
echo "Below you can see the logs produced by the applications that just started."
echo ""

set -x
timeout 5 ./dev docker-logs
./dev docker-list-all
set +x

echo -e "\n\n\n"
echo "### ### ### ### ###"
echo -n "3. We will run our functional tests (and they should mostly pass). Proceed? (y/n) "
yn_prompt

set -x
./dev docker-run-functional-tests
set +x

echo "That's all folks! Shutting down everything."
./dev docker-stop-all

echo -e "\n\n\n"
echo "### ### ### ### ###"
echo "For more information, checkout our README.md and docs/ directory."
echo "Thanks!"