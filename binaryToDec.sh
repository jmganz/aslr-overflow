#!/bin/bash
line1=""
line2=""
line3=""
line4=""
while read line
do
  read -ra ADDR1 <<< "$((2#${line:0:8}))"
  read -ra ADDR2 <<< "$((2#${line:8:8}))"
  read -ra ADDR3 <<< "$((2#${line:16:8}))"
  read -ra ADDR4 <<< "$((2#${line:24:8}))"
  line1="$line1, ${ADDR1}"
  line2="$line2, ${ADDR2}"
  line3="$line3, ${ADDR3}"
  line4="$line4, ${ADDR4}"
done < $1
echo "${1:8}"
echo "${line1:2}"
echo "${line2:2}"
echo "${line3:2}"
echo "${line4:2}"
