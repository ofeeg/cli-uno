#!/bin/bash

object_files=$(find *.o)


for file in $object_files
do
    gcc  $file tests/${file:0:-2}_test.c -o ${file:0:-2}
    done
