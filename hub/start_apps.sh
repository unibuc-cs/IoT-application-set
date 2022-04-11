#!/bin/sh

# Modify each line as following 's/<app_name>:[0-9][0-9][0-9][0-9]/<hostname>:<port>/g/'

(cd ../apps/smartkettle; ./run.sh 9081 &)
(cd ../apps/flowerpower; ./run.sh 9082 &)
(cd ../apps/smarttv; ./run.sh 9083 &)
(cd ../apps/windwow; ./run.sh 9084 &)
(cd ../apps/windwow; python3 -u app.py &)

