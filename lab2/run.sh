#!/bin/bash
read -a a
./bin/run ${a[0]} < run.in > run.out
