#!/bin/bash

rm -f *.json
rm -f *.cc
rm -f x509up_*
rm -f *.sub
rm -f *.root

if [[ $1 == DIRECTORIES ]] || [[ $1 == ALL ]];then
    for DIR in `find -mindepth 1 -type d`;do
	echo "Removing $DIR"
	rm -rf $DIR
    done
fi

