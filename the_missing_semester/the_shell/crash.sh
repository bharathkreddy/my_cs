#! /usr/bin/env sh

n=$(( RANDOM % 100 ))

if [[ n -eq 42 ]]; then
  echo "$(date): Error: 42 caused crash, exiting." >&2
  # binds the message to stderr stream.
  exit 1;
  else echo "$(date): $n";

fi