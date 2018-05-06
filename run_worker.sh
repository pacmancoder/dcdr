rm -r ./dcdr-scene/scenes_tmp
mkdir ./dcdr-scene/scenes_tmp

./build-debug/bin/dcdr-worker-cli --ip "127.0.0.1" --port "61297" --scene-cache "$PWD/dcdr-scene/scenes_tmp"
DCDR_WORKER_PID=$!
