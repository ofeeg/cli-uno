#!/bin/bash

object_files=$(find *.o)


for file in $object_files
do
    line=$(grep ${file:0:-2}_test depends | cut -d ' ' -f2-)
    newline=$(for word in $(basename -as .h $line) ; do echo ${word}.o ; done)
    gcc  $newline  tests/${file:0:-2}_test.c -o ${file:0:-2} #>&/dev/null
done
