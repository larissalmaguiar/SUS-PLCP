#! /bin/sh

mkdir -p results 

for i in ../dataset/COVID/*; do 

    test=${i##*/}; 
    date >> results/${test}
    echo "####";
    echo ${test}; 
    ls -lah $i

    for j in {0..3}; do 
        echo ALG $j; 
        ../main-sus $i -A $j -t >> results/${test};
        echo "" >> results/${test};
        echo ""
    done;
done;

