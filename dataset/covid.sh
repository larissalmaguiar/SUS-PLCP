#! /bin/sh

mkdir -p results 

for i in ../dataset/COVID/*; do 

    test=${i##*/}; 
    date >> /SUS-PLCP/dataset/results/${test}
    echo "####";
    echo ${test}; 
    ls -lah $i

    for j in {0..3}; do 
        echo ALG $j; 
        ../main-sus $i -A $j -t >> /SUS-PLCP/dataset/results/${test};
        echo "" >> /SUS-PLCP/dataset/results/${test};
        echo ""
    done;
done;

