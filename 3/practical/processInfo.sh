#!/bin/bash

pid=$1
re='^[0-9]+$'
if [[ $pid =~ $re ]] && [[ -d "/proc/$pid" ]] ; then
  read -r name < "/proc/$pid/status"
  name=${name:6}
  p=$(getconf PAGESIZE)
  s=$(cat "/proc/$pid/statm" | cut -d' ' -f 1)
  size=$(( $p * $s ))
  args=$(cat "/proc/$pid/cmdline" | cut -d $'\0' -f 2-)
  envvars=$(cat "/proc/$pid/environ")
  echo -e "Name: $name\nMemory: $size\nArgs: $args\nEnvironment Variables:\n$envvars"
else
  echo "There is no such process"
fi