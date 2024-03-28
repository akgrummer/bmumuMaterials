#!/bin/bash

TARGET=$1

if [[ ! -d $TARGET ]];then
    echo "Directory \"$TARGET\" does not exist."
    kill -INT $$
fi

for DIR in `find . -type d -name "plots_*"`;do
    echo "Copying $DIR"
    cp -r $DIR $TARGET
done
