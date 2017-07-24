#!/bin/bash

rm errorsot 2>&1 > /dev/null

DIRS=$1
for d in $DIRS
do
	FILES=$d/*
	echo "Files : $FILES"

	echo "in $d" >> errorsot

	for f in $FILES
	do
		echo "Processing file $f"
		TYPE=$(file $f)
		/usr/bin/otool -t $f > sysresot
		./otool $f > myresot
		DIFF=$(diff sysresot myresot)
		if [ "$DIFF" != "" ]
		then
			echo "ERROR while processing $f"
			echo "diff:"
			echo "$DIFF"
			echo "ERROR while processing $f" >> errorsot
		fi
	done
	echo "" >> errorsot
done
