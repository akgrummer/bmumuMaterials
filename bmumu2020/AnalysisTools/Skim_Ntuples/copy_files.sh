#!/bin/bash

copy_proxy()
{
    PROXY=$(find /tmp/ -maxdepth 1 -user $USER -type f -name x509up_* 2>&1 | grep -v "Permission denied")
    NFILES=${#PROXY[@]}

    if [[ $NFILES -ne 1 ]];then
        echo "Found $NFILES proxy files."
        kill -INT $$
    fi

    cp ${PROXY[0]} .
}

copy_proxy
