#!/bin/bash
for k in 1 2 3 5 7; do
  for k_fold in 2 5 10; do
    dir=resultados/knn/k_$k/k_fold_$k_fold;
    find $dir | grep clasif | xargs cat | sed -r -e 's/.*s([0-9]+).* ([0-9]+),/\1 \2/' | python resultados.py > resultados.csv;
    mv presicion.png $dir/;
    mv recall.png $dir/;
    mv resultados.csv $dir/;
  done
done
