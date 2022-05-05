#!/bin/bash

num=10

for i in $(seq 0 $(($num - 1))); do
    python3 patch.py $i
    cd ../executable
    make clean && make
    cd ../simulator/gem5
    build/X86/gem5.opt configs/example/l3se.py --env "env.txt" --num-cpu=2 --cpu-type="TimingSimpleCPU" --caches --l2cache --l3cache -c"../../executable/attacker;../../executable/victim"
    cd ../../analysis
    python3 decode.py
    python3 stat.py $i
done

