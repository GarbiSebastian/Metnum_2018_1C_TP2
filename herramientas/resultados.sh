#!/bin/bash
metodo=$1
dir_resultados=resultados;
if [[ $metodo -eq 1 ]];
then
  for k in 1 2 3 5 7; do
    for alfa in 1 2 3 5 7 10 20 30; do
      for k_fold in 2 5 10; do
        dir=$dir_resultados/metodo_$metodo/k_$k/alfa_$alfa/k_fold_$k_fold;
        find $dir | grep clasif | xargs cat | sed -r -e 's/.*s([0-9]+).* ([0-9]+),/\1 \2/' | python herramientas/resultados.py > resultados.csv;
        mv presicion.png $dir/;
        mv recall.png $dir/;
        mv accuracy.png $dir/;
        mv resultados.csv $dir/;
      done;
    done;
  done;
else
  for k in 1 2 3 5 7; do
    for k_fold in 2 5 10; do
      dir=$dir_resultados/metodo_$metodo/k_$k/k_fold_$k_fold;
      find $dir | grep clasif | xargs cat | sed -r -e 's/.*s([0-9]+).* ([0-9]+),/\1 \2/' | python herramientas/resultados.py > resultados.csv;
      mv presicion.png $dir/;
      mv recall.png $dir/;
      mv accuracy.png $dir/;
      mv resultados.csv $dir/;
    done;
  done;
fi
echo "resultados $metodo finalizado";
