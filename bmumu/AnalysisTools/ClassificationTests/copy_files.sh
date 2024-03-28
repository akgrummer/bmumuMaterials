#!/bin/bash

TARGET_IMAGES="/nfs/monet_3/home/campoverde/Presentations/Background_Classification/images/"
TARGET_SLIDES="/nfs/monet_3/home/campoverde/Presentations/Background_Classification/"
TARGET_TABLES="/nfs/monet_3/home/campoverde/Presentations/Background_Classification/"

if [[ $1 == "plots" ]];then
    if [[ -d $TARGET_IMAGES/Plots ]];then
	echo "Removing $TARGET_IMAGES/Plots"
	rm -rf $TARGET_IMAGES/Plots
    fi

    cp -r Plots $TARGET_IMAGES 
elif [[ $1 == "slides" ]];then
    if [[ -d $TARGET_SLIDES/Slides ]];then
	echo "Removing $TARGET_SLIDES/Slides"
	rm -rf $TARGET_SLIDES/Slides
    fi

    cp -r Slides $TARGET_SLIDES
elif [[ $1 == "tables" ]];then
    if [[ -d $TARGET_TABLES/Tables ]];then
	echo "Removing $TARGET_TABLES/Tables"
	rm -rf $TARGET_TABLES/Tables
    fi

    cp -r Tables $TARGET_TABLES
fi

