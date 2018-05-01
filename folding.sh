#!/bin/bash
sujetos=41;
imXsuj=10;
base=bases/baseCaras.csv;
for fold_tam in 1 2 5
do
  for fold_nro in $(seq -s' ' 1 $(($imXsuj/$fold_tam)))
  do
    #echo $fold_tam $fold_nro;
    cat $base | head -n $((fold_tam*fold_nro*sujetos)) | tail -n $((fold_tam*sujetos)) > tests/test_${fold_tam}_${fold_nro}.csv;
    cat $base $base | tail -n $(( (imXsuj*2-(fold_tam*fold_nro) )*sujetos)) | head -n $(( (imXsuj-fold_tam) * sujetos)) > tests/train_${fold_tam}_${fold_nro}.csv;
  done
done
