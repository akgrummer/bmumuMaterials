#!/bin/bash

TARGET="/nfs/monet_3/home/campoverde/Documents/ANA-BPHY-2018-09-INT1/tables/InternalNote_Samples/"
SOURCE="latex/"

if [ ! -d $TARGET ];then
    echo "Target not found:"
    echo "    $TARGET"
    kill -INT $$
fi

rm -f $TARGET/*.tex

cp $SOURCE/*.tex $TARGET

