#!/bin/sh

trap "" 15

ulimit -c 0

while true
do
  ./server &
  serverPID=$!
  ( sleep 200; kill $serverPID 2> /dev/null ) &
  wait $serverPID
  sleep 1
done
