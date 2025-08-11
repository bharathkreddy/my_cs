#! /usr/bin/env sh

for i in {1..100}
do
    ./crash.sh 2>>error.log
    # takes stderr ouput and binds it to stdout (can be a file instead.)
    # use >> to append else loop is going to overwrite prev loop
done
