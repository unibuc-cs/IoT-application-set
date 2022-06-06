#!/bin/sh

TIME=$1
COMMAND="$2 $3"

sleep $1
${COMMAND}
