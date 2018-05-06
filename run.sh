

./build-debug/bin/dcdr-server-cli --scene-cache "$PWD/dcdr-scene/scenes" &
DCDR_SERVER_PID=$!
sleep 1;

./build-debug/bin/dcdr-gui &
DCDR_GUI_PID=$!

read

kill $DCDR_GUI_PID
kill $DCDR_SERVER_PID

killall dcdr-gui
killall dcdr-server-cli

