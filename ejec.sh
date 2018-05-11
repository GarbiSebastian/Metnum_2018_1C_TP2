#!/bin/bash
base=baseCarasRed.csv; for i in {1..10};do for j in {$i..$((i+1))}grep $base -e /$i.pgm > tests/test_K10_$i.csv; grep $base -e /$i.pgm -v > tests/train_K10_$i.csv; done
base=baseCarasRed.csv; for i in {1..10..2};do imagenes="("; for ((j=i;j<i+1;j++ )); do imagenes="$imagenes"$j"|"; done; imagenes="$imagenes"$j")";done;echo $imagenes
