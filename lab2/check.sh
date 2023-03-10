#!/bin/bash

fp="tests/expected${1}.out"
if [[ ($(diff $fp ${2} | wc -m) == 0) ]]
then
	echo "test${1} passed"
else
	echo "test${1} failed"
fi
