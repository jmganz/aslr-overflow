#!/bin/sh

# CATCHING AND IGNORING SIGNAL 15 HELPS AVOID HANGS
trap "" 15

ulimit -c 0

# LOOP FOREVER
while true
do
  # THE FOLLOWING COMMENTED CODE WORKS BETTER IN LINUX
  #./server &
  #serverPID=$!
  #( sleep 200; kill $serverPID 2> /dev/null ) &
  #wait $serverPID
  # KILL CLIENT AFTER 60 SECONDS
  timeout -s 9 60 ./server
  sleep 1
done
