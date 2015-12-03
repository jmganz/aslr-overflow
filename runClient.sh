#!/bin/sh

ulimit -c 0

# LOOP 800 TIMES
for run in `jot 800 1`
do
  printf \\r$run
  # THE FOLLOWING COMMENTED CODE WORKS BETTER IN LINUX
  #./client >> $1 &
  #clientPID=$!
  #( sleep 200; kill $clientPID 2> /dev/null ) &
  #wait $clientPID
  # KILL CLIENT AFTER 60 SECONDS
  timeout -s 9 60 ./client >> $1
  sleep 2
done
