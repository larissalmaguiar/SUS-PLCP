#! /bin/sh

mkdir -p /SUS-PLCP/dataset/results 

for i in /SUS-PLCP/dataset/COVID/*; do 

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

