#!/bin/bash

rm errors 2>&1 > /dev/null

DIRS=$1
for d in $DIRS
do
	FILES=$d/*
	echo "Files : $FILES"

	echo "in $d" >> errors

	for f in $FILES
	do
		echo "Processing file $f"
		TYPE=$(file $f)
	#	if [ "$TYPE" != "$f: Mach-O 64-bit executable x86_64" ] && [ "$TYPE" != "$f: Mach-O 64-bit object x86_64" ]
	#	then
			# echo "ERROR - $TYPE"
	#		continue
	#	fi
		/usr/bin/nm $f > sysres
		./nm $f > myres
		DIFF=$(diff sysres myres)
		if [ "$DIFF" != "" ]
		then
			echo "ERROR while processing $f"
			echo "diff:"
			echo "$DIFF"
			echo "ERROR while processing $f" >> errors
			sleep 2;
		fi
	done
	echo "" >> errors
done
