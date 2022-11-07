#!/bin/bash
set -xeufo pipefail

test_flag="$( ./test/solve.py LOCAL | tr -d '\n' )"

actual_flag="$( cat ./flag.txt | tr -d '\n' )"

if [ "$test_flag" == "$actual_flag" ]; then
	echo "Success"
	exit 0
else
	echo "Failed"
	exit 1
fi
