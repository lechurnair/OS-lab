#!/bin/bash
cd $1
for f1 in *
do
	if [[ ! -d $f1 && ! -L $f1 && ! -p $f1 ]]
	then
		for f2 in *
		do
			if [[ ! -d $f2 && ! -L $f2 && ! -p $f2 && ($f1 != $f2) && ($(diff $f1 $f2 | wc -m) == 0) ]]
			then
				rm $f2
				ln -s $f1 $f2
			fi
		done
	fi
done