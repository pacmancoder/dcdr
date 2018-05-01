

./build-debug/bin/dcdr-server-cli --scene-cache "$PWD/dcdr-scene/scenes" &
DCDR_SERVER_PID=$!
sleep 1;

./build-debug/bin/dcdr-gui &
DCDR_GUI_PID=$!

rm -r ./dcdr-scene/scenes_tmp
mkdir ./dcdr-scene/scenes_tmp

./build-debug/bin/dcdr-worker-cli --scene-cache "$PWD/dcdr-scene/scenes_tmp" &
DCDR_WORKER_PID=$!

read

kill $DCDR_GUI_PID
kill $DCDR_WORKER_PID
kill $DCDR_SERVER_PID

killall dcdr-gui
killall dcdr-worker-cli
killall dcdr-server-cli

