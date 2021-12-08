#!/bin/sh

echo "1. Compile target"
dotnet RESTler/restler/Restler.dll compile --api_spec /target/openapi.yaml

echo "2. Fuzz target"
dotnet RESTler/restler/Restler.dll test --grammar_file ./Compile/grammar.py --dictionary_file ./Compile/dict.json --settings ./Compile/engine_settings.json --no_ssl

# Copy results outside of docker and change permissions and owner
cp -ar /Test/* /results
chmod -R 755 /results
chown -R 1000:1000 /results