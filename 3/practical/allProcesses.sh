#!/bin/bash

cd /proc
re='^[0-9]+$'
for f in * ; do
  if [[ $f =~ $re ]] ; then
    read -r name < $f/status
    name=${name:5}
    echo "$f $name"
  fi
done