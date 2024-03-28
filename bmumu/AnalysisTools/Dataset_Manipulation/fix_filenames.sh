#!/bin/bash

for FILE in `find -name "*.root*" -type f`;do
    if [[ $FILE =~ (.*\.root)\.[1-9]+ ]];then
	FILENAME=${BASH_REMATCH[1]}
	if [[ -f $FILENAME ]];then
	    echo "$FILENAME already exists"
	    kill -INT $$
	fi

	echo "$FILE"
	echo "$FILENAME"
	echo ""
	echo ""
	mv $FILE $FILENAME
    fi
done

