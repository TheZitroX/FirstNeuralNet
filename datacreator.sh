#!/bin/bash

echo "topology: 2 4 1"

# shellcheck disable=SC2034
for i in $(seq 1 50000); do
	# shellcheck disable=SC2004
	rnd=$(($RANDOM % 4))

	if [ $rnd -eq 0 ]
	then
		echo "in: 1.0 0.0"
		echo "out: 1.0"
	fi
	if [ $rnd -eq 1 ]
	then
		echo "in: 1.0 1.0"
		echo "out: 0.0"
	fi
	if [ $rnd -eq 2 ]
	then
		echo "in: 0.0 1.0"
		echo "out: 1.0"
	fi
	if [ $rnd -eq 3 ]
	then
		echo "in: 0.0 0.0"
		echo "out: 0.0"
	fi
done