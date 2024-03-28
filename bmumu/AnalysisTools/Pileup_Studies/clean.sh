#!/bin/bash

WHAT=$1

if [[ $WHAT == "PLOTS" ]];then
    for DIR in `find . -type d -name "plots*"`;do
	echo "Removing $DIR"
	rm -rf $DIR
    done
fi

if [[ $WHAT == "ROOT" ]];then
    rm -rf root/
fi


