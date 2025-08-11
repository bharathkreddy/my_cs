#! /usr/bin/env bash

echo "Starting the program at $(date)"
echo "Running the program $0 with $# arguments with pid $$"

for file in "$@"; do
  echo "$file";
  grep foob.txt "$file" > /dev/null 2> /dev/null
  # when pattern is not found, grep has exit status 1
  # redirect STDOUT and STDERR to a null register
  if [[ $? -ne 0 ]]; 
  then echo "File $file does not have any foob.txt";
  else echo "$file has foob.txt in it!!!!!FOUND!!!";
  fi
done