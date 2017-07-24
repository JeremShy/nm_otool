#!/bin/bash

rm errorsnm 2>&1 > /dev/null

DIRS=$1
for d in $DIRS
do
	FILES=$d/*
	echo "Files : $FILES"

	echo "in $d" >> errorsnm

	for f in $FILES
	do
		echo "Processing file $f"
		TYPE=$(file $f)
		/usr/bin/nm $f > sysresnm
		./nm $f > myresnm
		DIFF=$(diff sysresnm myresnm)
		if [ "$DIFF" != "" ]
		then
			echo "ERROR while processing $f"
			echo "diff:"
			echo "$DIFF"
			echo "ERROR while processing $f" >> errorsnm
		fi
	done
	echo "" >> errorsnm
done
