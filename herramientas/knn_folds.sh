#!/bin/bash
metodo=$1
#make tp;
dir_resultados=resultados;
dir_folds=folds;
for k in 1 2 3 5 7; do
	for k_fold in 2 5 10; do
		for iteracion in $(seq -s' ' 1 $k_fold); do
			fold_dir=$dir_folds/k_fold_$k_fold/iteracion_$iteracion;
			dir=$dir_resultados/metodo_$metodo/k_$k/k_fold_$k_fold/iteracion_$iteracion;
			mkdir -p $dir;
			comando="./tp2 -m $metodo -i $fold_dir/train.csv -q $fold_dir/test.csv -o $dir/clasif.csv -k $k > $dir/ejecucion.log 2> $dir/error.log;";
			echo "";
			echo $comando;
			eval $comando;
		done;
	done;
done;
echo "knn folds finalizado";
