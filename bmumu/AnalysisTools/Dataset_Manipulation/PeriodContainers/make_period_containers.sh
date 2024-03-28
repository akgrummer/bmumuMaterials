#!/bin/bash

#----------------------------------------
#----------------------------------------
make_container()
{
    YEAR=$1
    PERIOD=$2
    CONTAINER="user.acampove:user.acampove.data"$YEAR"_13TeV.period"$PERIOD".physics_Main.PhysCont.DAOD_BPHY8.grp16_v01_p3583"

    echo "Making Container $CONTAINER"

    rucio add-container $CONTAINER
}
#----------------------------------------
#Make containers
#----------------------------------------
make_container 15 A
make_container 15 C
make_container 15 D
make_container 15 E
make_container 15 F
make_container 15 G
make_container 15 H
make_container 15 J

make_container 16 A
make_container 16 B
make_container 16 C
make_container 16 D
make_container 16 E
make_container 16 F
make_container 16 G
make_container 16 I
make_container 16 K
make_container 16 L
#----------------------------------------
#----------------------------------------

