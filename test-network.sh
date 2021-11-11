#!/bin/sh

echo "All requests should respond with not found (404)"
set -x

curl -I -X GET http://localhost:9081/
curl -I -X GET http://localhost:9082/
curl -I -X GET http://localhost:9083/
curl -I -X GET http://localhost:9084/
curl -I -X GET http://localhost:9085/
