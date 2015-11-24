#!/bin/bash

for data in addresses.hardened64 addresses.hardened64.strong addresses.linux32 addresses.linux64
do
  python plot.addresses.py $data
  python flatten.addresses.py $data
done
