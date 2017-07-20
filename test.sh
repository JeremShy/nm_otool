#!/bin/bash

FILES=$1/*
echo "Files : $FILES"

rm errors

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
#		exit
		echo "ERROR while processing $f"
		echo "ERROR while processing $f" >> errors
		sleep 2;
	fi
done
