#!/bin/bash
metodo=$1
dir_resultados=resultados;
for k in `seq 1 2 50`; do
    for k_fold in 2 5 10; do
        if [[ $metodo -eq 1 ]] || [[ $metodo -eq 3 ]];
        then
            for alfa in `seq 5 5 200`; do
                dir=$dir_resultados/metodo_$metodo/k_$k/alfa_$alfa/k_fold_$k_fold;
                find $dir | grep clasif | xargs cat | sed -r -e 's/.*s([0-9]+).* ([0-9]+),/\1 \2/' | python herramientas/resultados.py > resultados.csv;
                mv presicion.png $dir/;
                mv recall.png $dir/;
                mv accuracy.png $dir/;
                mv resultados.csv $dir/;
            done;
        else
            dir=$dir_resultados/metodo_$metodo/k_$k/k_fold_$k_fold;
            find $dir | grep clasif | xargs cat | sed -r -e 's/.*s([0-9]+).* ([0-9]+),/\1 \2/' | python herramientas/resultados.py > resultados.csv;
            mv presicion.png $dir/;
            mv recall.png $dir/;
            mv accuracy.png $dir/;
            mv resultados.csv $dir/;
        fi;
    done;
done;
echo "resultados $metodo finalizado";
