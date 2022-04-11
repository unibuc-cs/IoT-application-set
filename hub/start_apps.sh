#!/bin/sh

(cd ../apps/smartkettle; ./run.sh 9081 &)
(cd ../apps/flowerpower; ./run.sh 9082 &)
(cd ../apps/smarttv; ./run.sh 9083 &)
(cd ../apps/windwow; ./run.sh 9084 &)
(cd ../apps/serasmart; ./run.sh 9085 &)
(cd ../hub/src; python3 -u app.py &)

