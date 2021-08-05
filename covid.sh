#! /bin/sh

mkdir -p results 

for i in /home/data/COVID/*; do 

	test=${i##*/}; 
	date >> results/${test}
	echo "####";
	echo ${test}; 
	ls -lah $i

	for j in {0..4}; do 
		echo ALG $j; 
		echo "./main-sus $i -A $j -t >> results/${test};"
	done;
done;
